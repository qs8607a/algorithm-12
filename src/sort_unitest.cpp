
#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtest/gtest.h>
#include <algorithm>
#include <stdint.h>
#include "sort.h"
    class SortTest : public ::testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(SortTest, binary_search) {
  std::vector<int> randomInt;
  randomInt.assign(8192, 0);
  std::generate(randomInt.begin(), randomInt.end(), rand);
  std::sort(randomInt.begin(), randomInt.end(), std::less<int>());
  for (auto iter = randomInt.begin(); iter != randomInt.end(); ++iter) {
    auto searchResult = slib::binary_search(randomInt.begin(), randomInt.end(),
                                            *iter, [](int i, int j) {
      return i - j;
    });
    ASSERT_TRUE(searchResult != randomInt.end());
    ASSERT_EQ(*iter, *searchResult);
  }
  /* 	for(int key : randomInt){
 		auto searchResult=slib::binary_search(randomInt.begin(),
 randomInt.end(),key,[](int i,int j){return i-j;});
 		ASSERT_TRUE(searchResult!=randomInt.end());
 		ASSERT_EQ(key,*searchResult);		
 	} */

}

TEST_F(SortTest, median3) {
  auto intcomp = [](int a, int b)->int { return a - b; }
  ;
  ASSERT_EQ(slib::median3(1, 2, 3, intcomp), 2);
  ASSERT_EQ(slib::median3(1, 3, 2, intcomp), 2);
  ASSERT_EQ(slib::median3(2, 1, 3, intcomp), 2);
  ASSERT_EQ(slib::median3(2, 3, 1, intcomp), 2);
  ASSERT_EQ(slib::median3(3, 1, 2, intcomp), 2);
  ASSERT_EQ(slib::median3(3, 2, 1, intcomp), 2);
  ASSERT_EQ(slib::median3(3, 2, 2, intcomp), 2);
}

TEST_F(SortTest, swapInt) {
  int a = 10, b = 30;
  slib::swap(a, b);
  ASSERT_EQ(a, 30);
  ASSERT_EQ(b, 10);
}

TEST_F(SortTest, isPowerOfTwo0) { ASSERT_FALSE(slib::isPowerOfTwo(0)); }

TEST_F(SortTest, isPowerOfTwo1) {
  //2的0次方是1，所以返回true
  ASSERT_TRUE(slib::isPowerOfTwo(1));
}

TEST_F(SortTest, isPowerOfTwo2) { ASSERT_TRUE(slib::isPowerOfTwo(2)); }

TEST_F(SortTest, isPowerOfTwo4) { ASSERT_TRUE(slib::isPowerOfTwo(4)); }

TEST_F(SortTest, swapString) {
  std::string a = "abc", b = "uhdufy7s3434fg";
  std::swap(a, b);
  ASSERT_STREQ(a.c_str(), "uhdufy7s3434fg");
  ASSERT_STREQ(b.c_str(), "abc");
}

TEST_F(SortTest, select_sort) {
  std::vector<int> randomInt;
  randomInt.assign(200, 0);
  std::generate(randomInt.begin(), randomInt.end(), rand);

  decltype(randomInt) intcopy(randomInt);
#if 0
  std::cout << "排序前:";
  std::copy(randomInt.begin(), randomInt.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
#endif
  slib::select_sort(randomInt.begin(), randomInt.end(), std::less<int>());
  std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
#if 0
  std::cout << "排序后:";
  std::copy(randomInt.begin(), randomInt.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "排序后:";
  std::copy(intcopy.begin(), intcopy.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
#endif
  ASSERT_TRUE(std::equal(randomInt.begin(), randomInt.end(), intcopy.begin()));
}

TEST_F(SortTest, bubble_sort) {
  std::vector<int> randomInt;
  randomInt.assign(200, 0);
  std::generate(randomInt.begin(), randomInt.end(), rand);

  decltype(randomInt) intcopy(randomInt);
  slib::bubble_sort(randomInt.begin(), randomInt.end(), std::less<int>());
  std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
  ASSERT_TRUE(std::equal(randomInt.begin(), randomInt.end(), intcopy.begin()));
}

TEST_F(SortTest, quick_sort) {
  std::vector<int> randomInt;
  randomInt.assign(100000, 0);
  std::generate(randomInt.begin(), randomInt.end(), rand);

  decltype(randomInt) intcopy(randomInt);
  slib::quick_sort(randomInt.begin(), randomInt.end(), [](int a, int b)->int {
    return a - b;
  });
  std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
  ASSERT_TRUE(std::equal(randomInt.begin(), randomInt.end(), intcopy.begin()));
}

TEST_F(SortTest, heap_sort) {
  std::vector<int> randomInt;
  randomInt.assign(200, 0);
  std::generate(randomInt.begin(), randomInt.end(), rand);

  decltype(randomInt) intcopy(randomInt);
  slib::heap_sort(randomInt.begin(), randomInt.end(), std::less<int>());
  std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
  //ASSERT_TRUE(std::equal(randomInt.begin(),randomInt.end(),intcopy.begin()));
}

TEST_F(SortTest, reverseBits) {
  uint8_t zero = 0;
  ASSERT_EQ(slib::reverseBits(zero), 0);
  ASSERT_EQ(slib::reverseBits((uint8_t) 1), 1 << 7);
  ASSERT_EQ(slib::reverseBits((uint16_t) 1), 1 << 15);
  ASSERT_EQ(slib::reverseBits((uint32_t) 1), 1 << 31);
  ASSERT_EQ(slib::reverseBits((uint64_t) 1), ((uint64_t) 1) << 63);
}

int main(int argc, char* argv[]) {
  srand((unsigned) time(NULL));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}