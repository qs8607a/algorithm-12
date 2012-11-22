#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtest/gtest.h>
#include <algorithm>
#include "sort.h"


class SortTest : public ::testing::Test {
public:		
	virtual void SetUp() {}	
	virtual void TearDown() {}
};

TEST_F(SortTest, swapInt) {
	int a=10,b=30;
	slib::swap(a,b);	
	ASSERT_EQ(a,30);
	ASSERT_EQ(b,10);
}

TEST_F(SortTest, isPowerOfTwo0) {	
	ASSERT_FALSE(slib::isPowerOfTwo(0));
}

TEST_F(SortTest, isPowerOfTwo1) {	
	//2的0次方是1，所以返回true
	ASSERT_TRUE(slib::isPowerOfTwo(1));
}

TEST_F(SortTest, isPowerOfTwo2) {	
	ASSERT_TRUE(slib::isPowerOfTwo(2));
}

TEST_F(SortTest, isPowerOfTwo4) {	
	ASSERT_TRUE(slib::isPowerOfTwo(4));
}


TEST_F(SortTest, swapString) {
	std::string a="abc",b="uhdufy7s3434fg";
	std::swap(a,b);
	ASSERT_STREQ(a.c_str(),"uhdufy7s3434fg");
	ASSERT_STREQ(b.c_str(),"abc");	
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
	ASSERT_TRUE(std::equal(randomInt.begin(),randomInt.end(),intcopy.begin()));
}

TEST_F(SortTest, bubble_sort) {
	std::vector<int> randomInt;
	randomInt.assign(200, 0);
	std::generate(randomInt.begin(), randomInt.end(), rand);

	decltype(randomInt) intcopy(randomInt);
	slib::bubble_sort(randomInt.begin(), randomInt.end(), std::less<int>());
	std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
	ASSERT_TRUE(std::equal(randomInt.begin(),randomInt.end(),intcopy.begin()));
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
	uint8_t zero=0;
	ASSERT_EQ(slib::reverseBits(zero),0);
	ASSERT_EQ(slib::reverseBits((uint8_t)1),1<<7);
	ASSERT_EQ(slib::reverseBits((uint16_t)1),1<<15);
	ASSERT_EQ(slib::reverseBits((uint32_t)1),1<<31);
	ASSERT_EQ(slib::reverseBits((uint64_t)1),1L<<63);
}


int main(int argc,char* argv[]){
	srand((unsigned) time(NULL));		
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}