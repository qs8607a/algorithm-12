#if HAVE_CONFIG_H
# include <config.h>
#endif


#ifdef HAVE_CPP_THREAD_H
#include <thread>
#else
#include <tbb/compat/thread>
#endif
#include <vector>
#include <tbb/mutex.h>

#include <tbb/tick_count.h>
#include <iostream>
#include <functional>

static int counter1=0;
static int loop_times=100000;
void test_thread_func1(tbb::mutex& lock){
  for(int i=0;i!=loop_times;++i){
	lock.lock();
	counter1++;
	lock.unlock();
  }
}

int main(int argc,char* argv[]){
	tbb::mutex lock;
	const int threadCount=10;
	std::vector<std::thread*> threads; 
	tbb::tick_count t0 = tbb::tick_count::now();
	for(int i=0;i!=threadCount;++i){
		threads.push_back(new std::thread(test_thread_func1,std::ref(lock)));
	}
	for(auto i=threads.begin();i!=threads.end();++i){
		std::thread* t=*i;
		t->join();
		delete t;
	}
	tbb::tick_count t1 = tbb::tick_count::now();	
	std::cout<<"time for action = "<<(t1-t0).seconds()<<" seconds\n";
	
}
