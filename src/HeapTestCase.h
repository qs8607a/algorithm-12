/*
 * HeapTestCase.h
 *
 *  Created on: Mar 9, 2010
 *      Author: Changming Sun
 */

#ifndef HEAPTESTCASE_H_
#define HEAPTESTCASE_H_

#include "MallocAllocator.h"
#include "Heap.h"

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

class HeapTestCase : public CppUnit::TestFixture {
 public:
  static CppUnit::TestSuite *suite() {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;
    suiteOfTests->addTest(new CppUnit::TestCaller<HeapTestCase>(
        "test_add", &HeapTestCase::test_add));
    return suiteOfTests;
  }

  void test_add() {
    slib::Heap<int, std::less_equal<int>, slib::MallocAllocator> h(10);
    std::vector<int> randomInt;
    randomInt.assign(100, 0);
    std::generate(randomInt.begin(), randomInt.end(), rand);
    for (std::vector<int>::iterator i = randomInt.begin(); i != randomInt.end();
         ++i) {
      h.add(*i);
    }
    h.outputAsGraph("test_add.png");
    CPPUNIT_ASSERT_MESSAGE("heap validate fail", h.validate());
  }

  void setUp() { srand((unsigned) time(NULL)); }

};

#endif /* HEAPTESTCASE_H_ */
