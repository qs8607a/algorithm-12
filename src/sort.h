#pragma once

//#include <algorithm>
#include <functional>
#include <limits.h> //CHAR_BIT

namespace slib {

	template <typename T>
	void swap(T& left,T& right){
		T tmp=left;
		left=right;
		right=tmp;
	}

	/**
	* 判断一个整数是不是2的次方
	*/
	template <typename T>
	bool isPowerOfTwo(T input){
		return input && !(input & (input -1));
	}

	/**
	 * 在[first,last)中进行二分查找。输入集必须已经排好序。即，如果iter1<iter2，则comp(iter1,iter2)<=0。
	 */
	template <typename RandomAccessIterator, typename T,typename Compare>
	RandomAccessIterator binary_search ( RandomAccessIterator first, RandomAccessIterator last,
		const T& key, Compare comp  ){
			for(auto lim = last - first; lim !=0; lim >>=1){
				auto mid=first + (lim >> 1);
				auto cmp=comp(key, *mid);
				if(cmp==0){ //found
					return mid;
				} else if(cmp > 0){
					/* key > p: move right */
					first = mid + 1;
					lim --;
				} else {
					//nothing;
				}
			}
			return last;
	}

	/**
	*  @brief  Return the minimum element in a range using comparison functor.
	*  @param  first  Start of range.
	*  @param  last   End of range.
	*  @param  comp   Comparison functor.
	*  @return  Iterator referencing the first instance of the smallest value
	*  according to comp.
	*/
	template<typename ForwardIterator, typename Compare>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last,
		Compare comp) {

			if (first == last)
				return first;
			ForwardIterator result = first;
			while (++first != last)
				if (comp(*first, *result))
					result = first;
			return result;
	}

	/**
	* \brief 冒泡排序
	* \param[in,out] first 排序的起始位置,必须是一个Forward Iterator,即必须支持运算符++
	* \param[in,out] last  排序的终止位置.必须是一个Forward Iterator,即必须支持运算符++
	* \param[in]     comp  比较函数,Binary Function.适合(即顺序符合要求)则返回true,否则返回false.
	*                      如果需要从小往大排，传入std::less即可，反之则std::greater.
	*
	*/

	template<class Iterator, typename BinaryPredicate>
	void bubble_sort(Iterator first, Iterator last, BinaryPredicate comp) {
		bool swaped = true; //本趟比较中是否发生了元素交换动作。如果否，则可停止。
		do {
			swaped = false;
			Iterator left;
			for (Iterator j = first;;) {
				left = j++;
				if (j >= last)
					break;
				if (comp(*j, *left)) { //如果这个Iterator严格符合STL中Forward Iterator的定义，那么当有*j++这样一个成员函数。
					swap(*j, *left); //HP STL中含有swap_iter函数，事实证明这个函数是多么的重要。
					swaped = true;
				}
			}
			last = left; //此时的t必定指向last的前一个元素。
		} while (swaped);
	}

	/**
	* \brief 冒泡排序,默认从小向大排列
	* \param[in,out] first 排序的起始位置,必须是一个Forward Iterator,即必须支持运算符++
	* \param[in,out] last  排序的终止位置(past-the-end).必须是一个Forward Iterator,即必须支持运算符++
	*
	*/

	template<class Iterator>
	void bubble_sort(Iterator first, Iterator last) {
		bubble_sort(first, last, std::less<int>());
	}

	/** \brief 选择排序
	* \param[in,out] first 排序的起始位置,必须是一个Forward Iterator,即必须支持运算符++
	* \param[in,out] last  排序的终止位置(past-the-end).必须是一个Forward Iterator,即必须支持运算符++
	* \param[in]     comp  比较函数,Binary Function.适合(即顺序符合要求)则返回true,否则返回false.
	*                      如果需要从小往大排，传入std::less即可，反之则std::greater.
	*
	*/

	template<class Iterator, typename BinaryPredicate>
	void select_sort(Iterator first, Iterator last, BinaryPredicate comp) {
		for (Iterator i = first; i != last; ++i) {
			Iterator t = slib::min_element(i, last, comp);
			swap(*i, *t);
		}
	}

	/** \brief 选择排序,默认从小向大排列
	* \param[in,out] first 排序的起始位置,必须是一个Forward Iterator,即必须支持运算符++
	* \param[in,out] last  排序的终止位置(past-the-end).必须是一个Forward Iterator,即必须支持运算符++
	*
	*/

	template<class Iterator>
	void select_sort(Iterator first, Iterator last) {
		select_sort(first, last, std::less<int>());
	}

	/** \brief 堆排序
	* \param[in,out] first 排序的起始位置,必须是一个Forward Iterator,即必须支持运算符++
	* \param[in,out] last  排序的终止位置(past-the-end).必须是一个Forward Iterator,即必须支持运算符++
	* \param[in]     comp  比较函数,Binary Function.适合(即顺序符合要求)则返回true,否则返回false.
	*                      如果需要从大往小排，传入std::less即可，反之则std::greater.
	*
	*
	* 算法复杂度: 平均时间 O(NlogN)
	*             最坏情况 O(NlogN)
	*             辅助空间 O(1)
	* 由于不清楚STL中make_heap的实现机制，所以这个函数实现的可能不尽人意
	* 比较后，对于其中任何两个相邻的iterator,均满足comp(i,1+i) ==false
	*/

	template<class Iterator, typename BinaryPredicate>
	void heap_sort(Iterator first, Iterator last, BinaryPredicate comp) {
		for (Iterator i = first; i != last; ++i) {
			//std::make_heap(i, last, comp);
		}
	}

	/* \brief 选择排序,默认从小向大排列
	* \param[in,out] first 排序的起始位置,必须是一个Forward Iterator,即必须支持运算符++
	* \param[in,out] last  排序的终止位置(past-the-end).必须是一个Forward Iterator,即必须支持运算符++
	*
	*/

	template <typename T>
	T roundup(T x,T y){
		return (((x+y-1)/y)*y);
	}

	template <typename T>
	T reverseBits(T v){
		T r = v;
		int s = sizeof(v) * CHAR_BIT - 1; // extra shift needed at end
		for (v >>= 1; v; v >>= 1)
		{   
			r <<= 1;
			r |= v & 1;
			s--;
		}
		r <<= s;
		return r;
	}

	/*
	void bucket_sort(uint64_t* first, uint64_t* last,uint64_t min,uint64_t max) {
	const size_t inputSize=last-first;
	const size_t bucketLength=roundup(inputSize,2);
	const uint64_t mask=reverseBits(bucketLength-1);
	std::list<uint64_t>* buckets=new std::list<uint64_t>[bucketLength];
	try{
	for(uint64_t* i=first;i!=last;++i){
	const uint64_t index= *i & mask;

	}
	}catch(...){
	delete[] buckets;
	throw ;
	}
	delete[] buckets;
	} */


	/* \brief 二路归并，将两个已排序的Container合并排序并输出
	* \param[in] source1_begin Container1的起始位置,必须是一个Input Iterator
	* \param[in] source1_end   Container1的终止位置(past-the-end),必须是一个Input Iterator
	* \param[in] source2_begin Container2的起始位置,必须是一个Input Iterator
	* \param[in] source2_end   Container2的终止位置,必须是一个Input Iterator
	* \param[out] dest         输出的起始位置，必须是一个Output Iterator
	* \param[in] comp          比较函数,Binary Function.适合(即顺序符合要求)则返回true,否则返回false.
	*                          如果需要从小往大排，传入std::less即可，反之则std::greater.
	*
	* 输出位置与输入位置千万不能相同，否则会导致不可预知的结果

	template<class InputIterator1, class InputIterator2, class OutputIterator,
	typename BinaryPredicate>
	void merge_2sorted_containers(InputIterator1 source1_begin,
	const InputIterator1 source1_end, InputIterator2 source2_begin,
	const InputIterator2 source2_end, OutputIterator dest,
	const BinaryPredicate comp) {
	while ((source1_begin != source1_end) && (source2_begin != source2_end))
	if (comp(*source1_begin, *source2_begin))
	*dest++ = *source1_begin++;
	else
	*dest++ = *source2_begin++;
	if (source1_begin != source1_end)
	std::copy(source1_begin, source1_end, dest);
	else
	std::copy(source2_begin, source2_end, dest);
	}
	*/
	//test for merge_2sorted_containers
	//int main(){
	//    int a[16];
	//    std::vector<int> v(32);
	//
	//    //用当前时间初始化随机函数
	//    srand( (unsigned)time( NULL ) );
	//
	//    //用随机数填充
	//    std::generate(a,a+16,rand);
	//    std::generate(v.begin(),v.end(),rand);
	//    
	//    std::cout<<"排序前:\n"
	//        <<"first:";
	//    std::copy(a,a+16,std::ostream_iterator<int>(std::cout," "));
	//    std::cout<<"\nsecond:";
	//    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
	//    std::cout<<std::endl;
	//    
	//
	//    //对两个分别进行排序
	//    std::sort(a,a+16);
	//    std::sort(v.begin(),v.end());
	//    std::cout<<"排序后:\n"
	//        <<"first:";
	//    std::copy(a,a+16,std::ostream_iterator<int>(std::cout," "));
	//    std::cout<<"\nsecond:";
	//    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
	//    std::cout<<std::endl;
	//
	//    //将排序后的数组和vector合并排序并输出
	//    std::cout<<"合并后:";
	//    merge_2sorted_containers(a,a+16,v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "),std::less<int>());
	//    
	//  return 0;
	//}


}
