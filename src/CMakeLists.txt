cmake_minimum_required (VERSION 2.6) 
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

#TARGET_LINK_LIBRARIES(simple  gtest mmgc)
add_executable(fib fib.cpp)
target_link_libraries(fib gtest ${CMAKE_THREAD_LIBS_INIT})
ADD_TEST(fib ${CMAKE_CURRENT_BINARY_DIR}/fib)

add_executable(heap_unitest heap_unitest.cpp heap.h  MallocAllocator.cpp MallocAllocator.h)
target_link_libraries(heap_unitest gtest ${CMAKE_THREAD_LIBS_INIT})
ADD_TEST(heap_unitest ${CMAKE_CURRENT_BINARY_DIR}/heap_unitest)

add_executable(RandomImpl1_unitest RandomImpl1_unitest.cpp)
target_link_libraries(RandomImpl1_unitest gtest ${CMAKE_THREAD_LIBS_INIT})
ADD_TEST(RandomImpl1_unitest ${CMAKE_CURRENT_BINARY_DIR}/RandomImpl1_unitest)

add_executable(arena_unitest arena_unitest.cpp arena.h arena.cpp)
target_link_libraries(arena_unitest gtest ${CMAKE_THREAD_LIBS_INIT})
ADD_TEST(arena_unitest ${CMAKE_CURRENT_BINARY_DIR}/arena_unitest)

add_executable(binarytree_unitest binarytree_unitest.cpp binarytree.h binarytree.cpp)
target_link_libraries(binarytree_unitest gtest ${CMAKE_THREAD_LIBS_INIT})
ADD_TEST(binarytree_unitest ${CMAKE_CURRENT_BINARY_DIR}/binarytree_unitest)

if(WIN32)
set(PLATFORM_SOURCE port_win32.h port_win32.cpp)
elseif(UNIX)
set(PLATFORM_SOURCE port_posix.h port_posix.cpp)
endif()


add_executable(port_unitest port_unitest.cpp ${PLATFORM_SOURCE})
target_link_libraries(port_unitest gtest)
ADD_TEST(port_unitest ${CMAKE_CURRENT_BINARY_DIR}/port_unitest)

add_executable(hash_unitest hash_unitest.cpp hash.h hash.cpp)
target_link_libraries(hash_unitest gtest ${CMAKE_THREAD_LIBS_INIT})
ADD_TEST(hash_unitest ${CMAKE_CURRENT_BINARY_DIR}/hash_unitest)

add_executable(skiplist_unitest skiplist_unitest.cpp skiplist.h ${PLATFORM_SOURCE} hash.cpp arena.cpp)
target_link_libraries(skiplist_unitest gtest)
target_link_libraries (skiplist_unitest  optimized ${TBB_LIB} )
target_link_libraries (skiplist_unitest  debug ${TBB_DEBUG_LIB})
ADD_TEST(skiplist_unitest ${CMAKE_CURRENT_BINARY_DIR}/skiplist_unitest)

add_executable(bloomfilter_unitest BloomFilter_unitest.cpp BloomFilter.h hash.h hash.cpp)
target_link_libraries(bloomfilter_unitest gtest)
ADD_TEST(bloomfilter_unitest ${CMAKE_CURRENT_BINARY_DIR}/bloomfilter_unitest)


#target_link_libraries(btree db)
