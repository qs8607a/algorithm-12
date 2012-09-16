cmake_minimum_required (VERSION 2.6) 
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
add_definitions(-DUNICODE -D_UNICODE -DOS_WIN)

#TARGET_LINK_LIBRARIES(simple  gtest mmgc)
add_executable(fib fib.cpp)
target_link_libraries(fib gtest)

add_executable(heap_unitest heap_unitest.cpp heap.h  MallocAllocator.cpp MallocAllocator.h)
target_link_libraries(heap_unitest gtest)

add_executable(RandomImpl1_unitest RandomImpl1_unitest.cpp)
target_link_libraries(RandomImpl1_unitest gtest)

add_executable(arena_unitest arena_unitest.cpp arena.h arena.cpp)
target_link_libraries(arena_unitest gtest)


add_executable(port_unitest port_unitest.cpp port_win32.h port_win32.cpp)
target_link_libraries(port_unitest gtest)

add_executable(hash_unitest hash_unitest.cpp hash.h hash.cpp)
target_link_libraries(hash_unitest gtest)

add_executable(skiplist_unitest skiplist_unitest.cpp skiplist.h port_win32.h port_win32.cpp hash.cpp arena.cpp)
target_link_libraries(skiplist_unitest gtest)
target_link_libraries (skiplist_unitest  optimized ${TBB_LIB} )
target_link_libraries (skiplist_unitest  debug ${TBB_DEBUG_LIB})


#target_link_libraries(btree db)
