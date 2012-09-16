
if DEBUG
AM_CXXFLAGS = -ggdb3 -fno-inline -O0 -Wall -Wextra -D_GLIBCXX_DEBUG_PEDANTIC -D_GLIBCXX_DEBUG 
AM_CXXFLAGS += -DACE_NTRACE=0 $(libgvc_CFLAGS)
endif


 
 noinst_LIBRARIES = libalgor.a
 libalgor_a_SOURCES = MallocAllocator.cpp
bin_PROGRAMS = hello heap

hello_SOURCES = main.cpp
hello_LDADD = libalgor.a
hello_CXXFLAGS = $(AM_CXXFLAGS)  $(ACE_CFLAGS) -std=gnu++0x
hello_LDADD +=  $(ACE_LIBS)

heap_SOURCES = heap.cpp
heap_LDADD = libalgor.a
heap_CXXFLAGS = $(AM_CXXFLAGS)  $(ACE_CFLAGS) $(libgvc_CFLAGS) -std=gnu++0x
heap_LDADD +=  $(ACE_LIBS) $(libgvc_LIBS)

check_PROGRAMS = checkSort checkHeap

checkSort_SOURCES = check1.cpp  SortTestCase.cpp 
checkSort_CXXFLAGS = $(AM_CXXFLAGS) $(ACE_CFLAGS) $(libgvc_CFLAGS)  -std=gnu++0x
checkSort_LDADD = $(CPPUNIT_LIBS) -ldmalloc $(ACE_LIBS) $(libgvc_LIBS) libalgor.a #-lqttestrunner

checkHeap_SOURCES = check1.cpp  HeapTestCase.cpp
checkHeap_CXXFLAGS = $(AM_CXXFLAGS) $(ACE_CFLAGS) $(libgvc_CFLAGS)  -std=gnu++0x
checkHeap_LDADD = $(CPPUNIT_LIBS) -ldmalloc $(ACE_LIBS) $(libgvc_LIBS) libalgor.a #-lqttestrunner

TESTS = $(check_PROGRAMS)
