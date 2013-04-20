
#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtest/gtest.h>

#include "BloomFilter.h"
#include "randomImpl1.h"
    class BloomFilterTest : public ::testing::Test {
  slib::Random* myrand;

  virtual void SetUp() {
    myrand = new slib::RandomImpl1((uint32_t) time(NULL));
  }

  virtual void TearDown() { delete myrand; }

 public:
  void getRandomString(int length, std::string& ret) {
    static const char* allchars =
        "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const int allCharsLength = 62;
    ret.resize(length);
    for (int i = 0; i != length; ++i) {
      int charIndex = myrand->Uniform(allCharsLength);
      ret[i] = allchars[charIndex];
    }
  }
};

TEST_F(BloomFilterTest, Test1) {
  const size_t keysCount = 20000;
  std::string* keys = new std::string[keysCount];
  for (int i = 0; i != keysCount; ++i) {
    getRandomString(20, keys[i]);
  }
  BloomFilter<std::string>* bf =
      BloomFilter<std::string>::create(keys, keysCount);
  int matchCount = 0;
  for (int i = 0; i != keysCount; ++i) {
    if (bf->KeyMayMatch(keys[i]))
      matchCount++;
  }
  std::cout << "match count=" << matchCount << std::endl;

  for (int i = 0; i != keysCount; ++i) {
    getRandomString(20, keys[i]);
  }

  int matchCount2 = 0;
  for (int i = 0; i != keysCount; ++i) {
    if (bf->KeyMayMatch(keys[i]))
      matchCount2++;
  }
  std::cout << "match count2=" << matchCount2 << std::endl;

  delete[] keys;

}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}