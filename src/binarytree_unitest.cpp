#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtest/gtest.h>

#include "binarytree.h"

class BinaryTreeTest : public ::testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(BinaryTreeTest, test1) {
  slib::BstNode<int> top;
  top.data = 1;
  slib::BstNode<int> node1;
  node1.data = 2;

}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}