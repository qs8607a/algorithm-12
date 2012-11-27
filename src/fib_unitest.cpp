#if HAVE_CONFIG_H
# include <config.h>
#endif


#include <iostream>
#include <gtest/gtest.h>

#include "fib.h"

class FibTest : public ::testing::Test {
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F(FibTest, test1) {
	EXPECT_EQ(1, slib::fib(1));
	EXPECT_EQ(1, slib::fib(2));
	EXPECT_EQ(2, slib::fib(3));
	EXPECT_EQ(3, slib::fib(4));
	EXPECT_EQ(5, slib::fib(5));
	EXPECT_EQ(8, slib::fib(6));
	EXPECT_EQ(13, slib::fib(7));
	EXPECT_EQ(21, slib::fib(8));
	EXPECT_EQ(34, slib::fib(9));
	EXPECT_EQ(55, slib::fib(10));
}

int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}
