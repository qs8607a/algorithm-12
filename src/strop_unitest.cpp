
#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtest/gtest.h>

#include "strop.h"
#include <algorithm>
#include <iostream>
    class StropTest : public ::testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(StropTest, test_strlen) {
  const char* s1 = "abc";
  EXPECT_EQ(3, slib::strlen(s1));
  const char s2[] = { 'k', 'b', '\0', 'a', 'c' };
  EXPECT_EQ(2, slib::strlen(s2));
}

TEST_F(StropTest, test_strncmp) {
  const char* s1 = "a";
  const char* s2 = "ab";
  std::cout << slib::strncmp(s1, s2, 4) << std::endl;
}

int main(int argc, char* argv[]) {
  srand((unsigned int) time(NULL));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
