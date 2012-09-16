#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <algorithm>
#include <iostream>
#include <gtest/gtest.h>

/**
* 以非递归的方式计算fib数列。
*/
int fib(int n){
	if(n<=2) return 1;
	else{
		int a(1),b(1);
		for(int i=2;i!=n;++i){
			b+=a;
			std::swap(a,b);
		}
		return a;
	}
}

class FibTest : public ::testing::Test {
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F(FibTest, test1) {
	EXPECT_EQ(1, fib(1));
	EXPECT_EQ(1, fib(2));
	EXPECT_EQ(2, fib(3));
	EXPECT_EQ(3, fib(4));
	EXPECT_EQ(5, fib(5));
	EXPECT_EQ(8, fib(6));
	EXPECT_EQ(13, fib(7));
	EXPECT_EQ(21, fib(8));
	EXPECT_EQ(34, fib(9));
	EXPECT_EQ(55, fib(10));
}

int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}

