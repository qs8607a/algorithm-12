#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtest/gtest.h>

#include "Array.h"

class ArrayTest : public ::testing::Test {
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(ArrayTest, test1) {
	EXPECT_EQ(1, 1);
}

int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}
