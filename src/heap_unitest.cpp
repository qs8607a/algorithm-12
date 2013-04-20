
#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtest/gtest.h>
#include "MallocAllocator.h"
#include "heap.h"
    class HeapTest : public ::testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(HeapTest, test1) {
  slib::Heap<int, std::less_equal<int>, slib::MallocAllocator> h(10);
  std::vector<int> randomInt(10000, 0);
  for (std::vector<int>::iterator i = randomInt.begin(); i != randomInt.end();
       ++i) {
    h.add(*i);
  }
  h.validate();
}
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
