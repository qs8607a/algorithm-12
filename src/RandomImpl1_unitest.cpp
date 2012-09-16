#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtest/gtest.h>

#include "randomImpl1.h"



class RandomTest : public ::testing::Test {
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(RandomTest, test1) {
	slib::RandomImpl1 rand((uint32_t)time(NULL));
	for(int i=0;i!=100;++i)
		rand.Next();
}
int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}
