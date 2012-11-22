#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtest/gtest.h>

#include "slist.h"


class SListTest : public ::testing::Test {
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(SListTest, test1) {	
	
}

int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}