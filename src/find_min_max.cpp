#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <algorithm>
#include <stdlib.h>
#include <functional>
#include <iostream>
#include <vector>
#include <openssl/rand.h>
#include <sys/time.h>


namespace slib{
   template <typename Iterator, typename Comp>
    std::pair<Iterator, Iterator> find_min_max_brute_force(Iterator begin,Iterator end,Comp greater){
        Iterator max=begin;
        Iterator min=begin;
        for(Iterator i=begin+1;i<end;++i){
            if(greater(*i,*max))
                max=i;
            else if(greater(*min,*i))
                min=i;
        }
        return std::make_pair(max, min);
    }
    
    template <typename Iterator, typename Comp>
    std::pair<Iterator, Iterator> find_min_max2(Iterator begin,Iterator end,Comp greater){
        if(begin+1>=end) return std::make_pair(begin, begin);
        auto len=end-begin;
        Iterator max=begin;
        Iterator min=begin;
        if(!len%2){
            if(greater(*begin,*max))
                max=begin;
            else if(greater(*min,*begin))
                min=begin;
            begin++;
        }
        for(Iterator i=begin+1;;){
            Iterator j=i++;
            if(i==end) break;
            //if(i>=end || j>=end) throw std::runtime_error("out of range!!");
            if(greater(*i,*j)){
                if(greater(*i,*max))
                    max=i;
                else if(greater(*min,*j))
                    min=j;
            } else {
                if(greater(*j,*max))
                    max=j;
                else if(greater(*min,*i))
                    min=i;
            }
            ++i;
        }
        return std::make_pair(max, min);
    }
}


static void test1(){
   
    std::vector<int> randomInt;
	randomInt.assign(1024*1024*64, 0);
	std::generate(randomInt.begin(), randomInt.end(), rand);
    
    auto ret=slib::find_min_max_brute_force(randomInt.begin(), randomInt.end(),std::greater<int>());
    std::cout<<"max="<<*ret.first<<",min="<<*ret.second<<std::endl;
}

#define MESURE_TIME_BEGIN(PREFIX) \
 timeval begin_##PREFIX,end_##PREFIX; \
 gettimeofday(&begin_ ## PREFIX ,NULL);


#define MESURE_TIME_END(PREFIX) {\
 timeval diff; \
 gettimeofday(&end_##PREFIX,NULL); \
 timersub(&end_##PREFIX,&begin_##PREFIX,&diff);\
 std::cout<<"total time="<<diff.tv_sec<<"秒"<<diff.tv_usec<<"微秒"<<std::endl;\
}

static std::string init_openssl_rand(){
    char seed_filename[4096];
    if(!RAND_file_name(seed_filename, sizeof(seed_filename)-1)) return "";
    seed_filename[sizeof(seed_filename)-1]='\0';
    RAND_load_file(seed_filename,-1);
    
    return seed_filename;
}

static void fini_openssl_rand(const char* seed_filename){
    RAND_write_file(seed_filename);
}

static void test2(){
    std::string seed_filename=init_openssl_rand();
    
    size_t count=1024*1024*64;
    std::unique_ptr<uint64_t[]> numbers(new uint64_t[count]);
    RAND_pseudo_bytes((unsigned char *)numbers.get(),count*sizeof(uint64_t));
    
    MESURE_TIME_BEGIN(T1)
    auto ret=slib::find_min_max_brute_force(numbers.get(), numbers.get()+count,[](uint64_t l,uint64_t r){return l<r;});
    MESURE_TIME_END(T1)
    
    std::cout<<"max="<<*ret.second<<",min="<<*ret.first<<std::endl;
    
    MESURE_TIME_BEGIN(T2)
    uint64_t max=*std::max_element(numbers.get(), numbers.get()+count);
    uint64_t min=*std::min_element(numbers.get(), numbers.get()+count);
    MESURE_TIME_END(T2)
    std::cout<<"max="<<max<<",min="<<min<<std::endl;

    
    MESURE_TIME_BEGIN(T3)
    auto ret2=std::minmax_element(numbers.get(), numbers.get()+count,[](uint64_t l,uint64_t r){return l<r;});
    MESURE_TIME_END(T3)
    std::cout<<"max="<<*ret2.second<<",min="<<*ret2.first<<std::endl;
    
    MESURE_TIME_BEGIN(T4)
    auto ret3=slib::find_min_max2(numbers.get(), numbers.get()+count,[](uint64_t l,uint64_t r){return l<r;});
    MESURE_TIME_END(T4)
    std::cout<<"max="<<*ret3.second<<",min="<<*ret3.first<<std::endl;

    fini_openssl_rand(seed_filename.c_str());
}


char* randomStringUsingStdRand(size_t len){
    char* buf(new char[len+1]);
    for(int i=0;i!=len;++i){
        buf[i]='a'+rand()%26;
    }
    buf[len]='\0';
    return buf;
}


static void test3(){
    std::string seed_filename=init_openssl_rand();
    
    size_t count=1024*1024*64;
    std::unique_ptr<char*[]> numbers(new char*[count]);
    for(int i=0;i!=count;++i){
        numbers[i]=randomStringUsingStdRand(20);
    }
    uint64_t comp_count=0;
    auto comp=[](const char* l,const char* r){return strcmp(l,r)<0;};
    MESURE_TIME_BEGIN(T1)
    auto ret=slib::find_min_max_brute_force(numbers.get(), numbers.get()+count,comp);
    std::cout<<"comp_count="<<comp_count<<std::endl;
    comp_count=0;
    MESURE_TIME_END(T1)
    
    std::cout<<"max="<<*ret.second<<",min="<<*ret.first<<std::endl;
    
    MESURE_TIME_BEGIN(T2)
    std::string max=*std::max_element(numbers.get(), numbers.get()+count,comp);
    std::string min=*std::min_element(numbers.get(), numbers.get()+count,comp);
    std::cout<<"comp_count="<<comp_count<<std::endl;
    comp_count=0;
    MESURE_TIME_END(T2)
    std::cout<<"max="<<max<<",min="<<min<<std::endl;
    
    
    MESURE_TIME_BEGIN(T3)
    auto ret2=std::minmax_element(numbers.get(), numbers.get()+count,comp);
    std::cout<<"comp_count="<<comp_count<<std::endl;
    comp_count=0;
    MESURE_TIME_END(T3)
    std::cout<<"max="<<*ret2.second<<",min="<<*ret2.first<<std::endl;
    
    fini_openssl_rand(seed_filename.c_str());
}

int main(){
    srand((unsigned)time(NULL));
    test2();
    return 0;
}
