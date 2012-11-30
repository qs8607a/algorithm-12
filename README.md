algorithm
=========

some algorithm test

To build this project,you need cmake 2.8 and ( Visual Studio 2010 Or gcc 4.7 on Linux)<br/>

Then, following these command:<br/>
1. svn co https://github.com/snnn/algorithm/trunk algorithm <br/>
2. cd algorithm <br/>
3. mkdir b1 <br/>
   cd b1 <br/>
   cmake .. <br/>
4. make <br/>
   make test <br/>


   
1. src/SkipList.h : A SkipList.
1. src/fib.cpp: 以非递归的方式计算fib数列。
1. src/heap.h: 数据结构，堆。
1. src/hash.cpp: 一个简单的hash函数。 char[] -> uint32_t
1. src/randomImpl1.h: LCG随机数生成器。
1. src/sort.h： 几种排序算法
1. src/TASLock.h: TAS spin-lock algorithm
1. src/TTASLock.h: TTAS spin-lock algorithm