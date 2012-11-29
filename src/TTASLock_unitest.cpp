#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtest/gtest.h>

#ifdef HAVE_CPP_THREAD_H
#include <thread>
#else
#include <tbb/compat/thread>
#endif

#include "TTASLock.h"

class TTASLockTest : public ::testing::Test {
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(TTASLockTest, test1) {
	slib::TTASLock lock;
	lock.lock();
	lock.unlock();
}

void test_thread_func1(slib::TTASLock& lock){
  for(int i=0;i!=100000;++i){
	lock.lock();
	lock.unlock();
  }
}

TEST_F(TTASLockTest, test2) {
	slib::TTASLock lock;
	const int threadCount=10;
	std::vector<std::thread*> threads; 
	for(int i=0;i!=threadCount;++i){
		threads.push_back(new std::thread(test_thread_func1,std::ref(lock)));
	}
	for(auto i=threads.begin();i!=threads.end();++i){
		std::thread* t=*i;
		t->join();
		delete t;
	}
}

int main(int argc,char* argv[]){
	::testing::InitGoogleTest(&argc, argv);  
	return RUN_ALL_TESTS();
}
