#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtest/gtest.h>

#ifdef HAVE_CPP_THREAD_H
#include <thread>
#else
#include <tbb/compat/thread>
#endif

#include <functional>  //std::ref
#include "ScopeGuard.h"
#include "TASLock.h"

class TASLockTest : public ::testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(TASLockTest, test1) {
  slib::TASLock lock;
  lock.lock();
  lock.unlock();
}

static int counter1 = 0;
static int loop_times = 100000;
void test_thread_func1(slib::TASLock& lock) {
  for (int i = 0; i != loop_times; ++i) {
    lock.lock();
    LOKI_ON_BLOCK_EXIT_OBJ(lock, &slib::TASLock::unlock);
    counter1++;
    //lock.unlock();
  }
}

TEST_F(TASLockTest, test2) {
  slib::TASLock lock;
  const int threadCount = 10;
  std::vector<std::thread*> threads;
  for (int i = 0; i != threadCount; ++i) {
    threads.push_back(new std::thread(test_thread_func1, std::ref(lock)));
  }
  for (auto i = threads.begin(); i != threads.end(); ++i) {
    std::thread* t = *i;
    t->join();
    delete t;
  }
  EXPECT_EQ(counter1, threadCount * loop_times);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
