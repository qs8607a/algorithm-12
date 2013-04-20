
#pragma once

#include <algorithm>
#include <functional>
#include <limits.h>  //CHAR_BIT
    namespace slib {

  template <typename T> void swap(T & left, T & right) {
    T tmp = left;
    left = right;
    right = tmp;
  }

  /**
 	* 判断一个整数是不是2的次方
 	*/
  template <typename T> bool isPowerOfTwo(T input) {
    return input && !(input & (input - 1));
  }

  /**
 	 *
 在[first,last)中进行二分查找。输入集必须已经排好序。即，如果iter1<iter2，则comp(iter1,iter2)<=0。
 	 */
  template <typename RandomAccessIterator, typename T, typename Compare>
  RandomAccessIterator binary_search(RandomAccessIterator first,
                                     RandomAccessIterator last, const T & key,
                                     Compare comp) {
    for (auto lim = last - first; lim != 0; lim >>= 1) {
      auto mid = first + (lim >> 1);
      auto cmp = comp(key, *mid);
      if (cmp == 0) {  //found
        return mid;
      } else if (cmp > 0) {
        /* key > p: move right */
        first = mid + 1;
        lim--;
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
  template <typename ForwardIterator, typename Compare>
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
 	* \param[in,out] first 排序的起始位置,必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in,out] last  排序的终止位置.必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in]     comp  比较函数,Binary
 Function.适合(即顺序符合要求)则返回true,否则返回false.
 	*
 如果需要从小往大排，传入std::less即可，反之则std::greater.
 	*
 	*/

  template <class Iterator, typename BinaryPredicate>
  void bubble_sort(Iterator first, Iterator last, BinaryPredicate comp) {
    bool swaped =
        true;  //本趟比较中是否发生了元素交换动作。如果否，则可停止。
    do {
      swaped = false;
      Iterator left;
      for (Iterator j = first;;) {
        left = j++;
        if (j >= last)
          break;
        if (comp(
                *j,
                *left)) {  //如果这个Iterator严格符合STL中Forward
                           //Iterator的定义，那么当有*j++这样一个成员函数。
          swap(
              *j,
              *left);  //HP
                       //STL中含有swap_iter函数，事实证明这个函数是多么的重要。
          swaped = true;
        }
      }
      last = left;  //此时的t必定指向last的前一个元素。
    } while (swaped);
  }

  /**
 	* \brief 冒泡排序,默认从小向大排列
 	* \param[in,out] first 排序的起始位置,必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in,out] last
 排序的终止位置(past-the-end).必须是一个Forward
 Iterator,即必须支持运算符++
 	*
 	*/

  template <class Iterator> void bubble_sort(Iterator first, Iterator last) {
    bubble_sort(first, last, std::less<int>());
  }

  /** \brief 选择排序
 	* \param[in,out] first 排序的起始位置,必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in,out] last
 排序的终止位置(past-the-end).必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in]     comp  比较函数,Binary
 Function.适合(即顺序符合要求)则返回true,否则返回false.
 	*
 如果需要从小往大排，传入std::less即可，反之则std::greater.
 	*
 	*/

  template <class Iterator, typename BinaryPredicate>
  void select_sort(Iterator first, Iterator last, BinaryPredicate comp) {
    for (Iterator i = first; i != last; ++i) {
      Iterator t = slib::min_element(i, last, comp);
      swap(*i, *t);
    }
  }

  /** \brief 选择排序,默认从小向大排列
 	* \param[in,out] first 排序的起始位置,必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in,out] last
 排序的终止位置(past-the-end).必须是一个Forward
 Iterator,即必须支持运算符++
 	*
 	*/

  template <class Iterator> void select_sort(Iterator first, Iterator last) {
    select_sort(first, last, std::less<int>());
  }

  /** \brief 堆排序
 	* \param[in,out] first 排序的起始位置,必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in,out] last
 排序的终止位置(past-the-end).必须是一个Forward
 Iterator,即必须支持运算符++
 	* \param[in]     comp  比较函数,Binary
 Function.适合(即顺序符合要求)则返回true,否则返回false.
 	*
 如果需要从大往小排，传入std::less即可，反之则std::greater.
 	*
 	*
 	* 算法复杂度: 平均时间 O(NlogN)
 	*             最坏情况 O(NlogN)
 	*             辅助空间 O(1)
 	*
 由于不清楚STL中make_heap的实现机制，所以这个函数实现的可能不尽人意
 	* 比较后，对于其中任何两个相邻的iterator,均满足comp(i,1+i)
 ==false
 	*/

  template <class Iterator, typename BinaryPredicate>
  void heap_sort(Iterator first, Iterator last, BinaryPredicate comp) {
    for (Iterator i = first; i != last; ++i) {
      //std::make_heap(i, last, comp);
    }
  }

  template <typename T> T roundup(T x, T y) { return (((x + y - 1) / y) * y); }

  template <typename T> T reverseBits(T v) {
    T r = v;
    int s = sizeof(v) * CHAR_BIT - 1;  // extra shift needed at end
    for (v >>= 1; v; v >>= 1) {
      r <<= 1;
      r |= v & 1;
      s--;
    }
    r <<= s;
    return r;
  }

  template <typename T, typename BinaryPredicate>
  T median3(T a, T b, T c, BinaryPredicate comp) {
    return comp(a, b) < 0 ? (comp(b, c) < 0 ? b : comp(a, c) < 0 ? c : a)
                          : (comp(b, c) < 0 ? (comp(a, c) < 0 ? a : c) : b);
  }

  template <typename T, typename BinaryPredicate>
  T median3Iter(T a, T b, T c, BinaryPredicate comp) {
    return comp(*a, *b) < 0
               ? (comp(*b, *c) < 0 ? b : comp(*a, *c) < 0 ? c : a)
               : (comp(*b, *c) < 0 ? (comp(*a, *c) < 0 ? a : c) : b);
  }

  template <typename T, typename BinaryPredicate>
  T median3AdjIter(T p, BinaryPredicate comp) {
    auto a = *p;
    auto b = *++p;
    auto c = *++p;
    return comp(a, b) < 0
               ? (comp(b, c) < 0 ? p + 1 : comp(a, c) < 0 ? p + 2 : p)
               : (comp(b, c) < 0 ? (comp(a, c) < 0 ? p : p + 2) : p + 1);
  }

  template <typename Iterator, typename BinaryPredicate>
  void quick_sort(Iterator begin, Iterator end, BinaryPredicate comp) {
    //elements in [begin,pa) always equals *begin
    //elements in (end,pd) always equals *begin
    //elements in [begin,pb) always less than or equals *begin
    //elements in (pc,end) always greater than or equals *begin
    Iterator pa, pb, pc, pd;
    //Now pa,pb points to the second element in [begin,end)
    pa = pb = begin + 1;
    pc = pd = end - 1;

    auto len = end - begin;
    if (false && len > 40) {
      Iterator pm = begin + len / 2;
      auto d = len / 8;
      //swap(*begin,*median3Iter(median3Iter(begin,begin+d,begin+d+d,comp),median3Iter(pm-d,pm,pm+d,comp),median3Iter(pd-d-d,pd-d,pd,comp),comp));
      swap(*begin, *median3Iter(median3AdjIter(begin, comp),
                                median3AdjIter(pm - d, comp),
                                median3AdjIter(pd - d - d, comp), comp));
    } else if (len > 7) {
      Iterator pm = begin + len / 2;
      swap(*begin, *median3Iter(begin, pm, pd, comp));
    }

    //pb always >= pa
    //pd always >= pc
    while (true) {
      int cmp_result;
      //把pb往右挪，直到找到大于a的
      while (pb < pc && (cmp_result = comp(*pb, *begin)) <= 0) {
        if (cmp_result == 0) {
          std::swap(*pa, *pb);
          pa++;
        }
        pb++;
      }
      //把pc往左挪，直到找到小于a的
      while (pb <= pc && (cmp_result = comp(*pc, *begin)) >= 0) {
        if (cmp_result == 0) {
          std::swap(*pc, *pd);
          pd--;
        }
        pc--;
      }
      if (pb > pc)
        break;
      swap(*pb, *pc);
      pb++;
      pc--;
    }
    //a pa pc pb pd
    auto r = std::min(pa - begin, pb - pa);
    std::swap_ranges(begin, begin + r, pb - r);
    r = std::min(pd - pc, end - pd - 1);
    std::swap_ranges(pb, pb + r, end - r);
    if ((r = pb - pa) > 1) {
      quick_sort(begin, begin + r, comp);
    }
    if ((r = pd - pc) > 1) {
      quick_sort(end - r, end, comp);
      //begin=end-r;
      //goto loop;
    }
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
 	* \param[in] source1_begin Container1的起始位置,必须是一个Input
 Iterator
 	* \param[in] source1_end
 Container1的终止位置(past-the-end),必须是一个Input Iterator
 	* \param[in] source2_begin Container2的起始位置,必须是一个Input
 Iterator
 	* \param[in] source2_end   Container2的终止位置,必须是一个Input
 Iterator
 	* \param[out] dest         输出的起始位置，必须是一个Output
 Iterator
 	* \param[in] comp          比较函数,Binary
 Function.适合(即顺序符合要求)则返回true,否则返回false.
 	*
 如果需要从小往大排，传入std::less即可，反之则std::greater.
 	*
 	*
 输出位置与输入位置千万不能相同，否则会导致不可预知的结果
 
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

}
