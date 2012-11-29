cmake_minimum_required (VERSION 2.6) 
project (algorithm)
find_package (Threads)
ENABLE_TESTING()

INCLUDE (CheckIncludeFiles)
INCLUDE (CheckIncludeFileCXX)

if(WIN32)
SET(GLOG_LIB libglog)
SET(TBB_DEBUG_LIB tbb_debug)
SET(TBB_LIB tbb)
add_definitions(-DUNICODE -D_UNICODE -DPLATFORM_WIN32 -DOS_WIN -DCOMPILER_MSVC -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS -DHAVE_CONFIG_H)
elseif(UNIX)
set(CMAKE_CXX_FLAGS "--std=c++11 -pthread")
SET(GLOG_LIB glog)
SET(TBB_DEBUG_LIB tbb)
SET(TBB_LIB tbb)
add_definitions(-DPLATFORM_POSIX -DHAVE_CONFIG_H)
endif()

CHECK_INCLUDE_FILE_CXX(thread HAVE_CPP_THREAD_H)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

ADD_SUBDIRECTORY(gtest)
ADD_SUBDIRECTORY(smhash)
ADD_SUBDIRECTORY(src)
