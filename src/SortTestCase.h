/*
 * SortTestCase.h
 *
 *  Created on: Feb 28, 2010
 *      Author: Changming Sun
 */

#ifndef SORTTESTCASE_H_
#define SORTTESTCASE_H_


#include <ace/OS.h>
#include <ace/Log_Msg.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include "sort.h"

class SortTestCase: public CppUnit::TestFixture {
private:
	std::vector<int> randomInt;
	std::vector<char> randomChar;
	std::vector<double> randomDouble;
public:
	virtual ~SortTestCase() {
	}

	void test_swap_int() {
		ACE_TRACE(__func__);
		int a=10,b=30;
		std::swap(a,b);
		CPPUNIT_ASSERT_MESSAGE("swap fail",a==30 && b==10);
	}

	void test_swap_string() {
		ACE_TRACE(__func__);
			std::string a="abc",b="uhdufy7s3434fg";
			std::swap(a,b);
			CPPUNIT_ASSERT_MESSAGE("swap fail",a=="uhdufy7s3434fg" && b=="abc");
		}

	void test_select_sort() {
		ACE_TRACE(__func__);
		decltype(randomInt) intcopy(randomInt);
#if 0
		std::cout << "排序前:";
		std::copy(randomInt.begin(), randomInt.end(),
				std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
#endif
		slib::select_sort(randomInt.begin(), randomInt.end(), std::less<int>());
		std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
#if 0
		std::cout << "排序后:";
		std::copy(randomInt.begin(), randomInt.end(),
				std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;

		std::cout << "排序后:";
		std::copy(intcopy.begin(), intcopy.end(),
				std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
#endif
		CPPUNIT_ASSERT_MESSAGE("compare faild",std::equal(randomInt.begin(),randomInt.end(),intcopy.begin()));
	}

	void test_bubble_sort() {
		ACE_TRACE(__func__);
		decltype(randomInt) intcopy(randomInt);
		slib::bubble_sort(randomInt.begin(), randomInt.end(), std::less<int>());
		std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
		CPPUNIT_ASSERT_MESSAGE("compare faild",std::equal(randomInt.begin(),randomInt.end(),intcopy.begin()));
	}

	void test_heap_sort() {
		ACE_TRACE(__func__);
		decltype(randomInt) intcopy(randomInt);
		slib::heap_sort(randomInt.begin(), randomInt.end());
		std::sort(intcopy.begin(), intcopy.end(), std::less<int>());
		CPPUNIT_ASSERT_MESSAGE("compare faild",std::equal(randomInt.begin(),randomInt.end(),intcopy.begin()));
	}

	 CPPUNIT_TEST_SUITE(SortTestCase);
	 CPPUNIT_TEST(test_swap_int);
	 CPPUNIT_TEST( test_swap_string);
	 CPPUNIT_TEST(test_select_sort);
	 CPPUNIT_TEST(test_bubble_sort);
	 CPPUNIT_TEST_SUITE_END();
public:
	void setUp() {
		srand((unsigned) time(NULL));
		ACE_DEBUG((LM_INFO,ACE_TEXT("%Igenerate ints\n")));
		randomInt.assign(2000, 0);
		randomChar.assign(100, 0);
		randomDouble.assign(100, 0);
		std::generate(randomInt.begin(), randomInt.end(), rand);
	}

};

#endif
