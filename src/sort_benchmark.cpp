#include <iostream>
#include <memory>
#include "sort.h"

inline int comp(const void* a,const void* b) __attribute__((pure));
inline int comp(const void* a,const void* b){return *(int*)a-*(int*)b;}

int main(){
  srand((unsigned)time(NULL));

  const size_t len=100000000;
  auto num=std::unique_ptr<int[]>(new int[len]);
  auto end=num.get()+len;
  std::generate(num.get(),end,rand);

  slib::quick_sort(num.get(),end,[](int a,int b) -> int {return a-b;});
  //qsort(num.get(),len,sizeof(int),comp);
  //std::sort(num.get(), end, std::less<int>());
  //std::sort(num.get(), end);
  //slib::bubble_sort(num.get(),end,[](int a,int b) -> int {return a-b;});
  return 0;
}
