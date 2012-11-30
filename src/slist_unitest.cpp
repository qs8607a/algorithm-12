#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtest/gtest.h>

#include "slist.h"
#include <algorithm>
#include <iostream>

class SListTest : public ::testing::Test {
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(SListTest, test_add) {	
	slib::LinkedList<int> list;
	for(int i=0;i!=10000;++i){
		list.append(i);
	}
	std::for_each(list.begin(),list.end(),[](int i){std::cout<<i<<std::endl;});
}

int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}