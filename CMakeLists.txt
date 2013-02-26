cmake_minimum_required (VERSION 2.6)
project (algorithm)
find_package (Threads)
find_package (OpenSSL)
ENABLE_TESTING()

INCLUDE (CheckIncludeFiles)
INCLUDE (CheckIncludeFileCXX)

SET(TBB_DEBUG_LIB tbb_debug)
SET(TBB_LIB tbb)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
include_directories(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
#set(CMAKE_XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES "YES")
set(GLOG_LIB glog)
add_definitions(-DPLATFORM_POSIX -DOS_MACOSX -DHAVE_CONFIG_H)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(CMAKE_CXX_FLAGS "--std=c++11 -pthread")
SET(GLOG_LIB glog)
add_definitions(-DPLATFORM_POSIX -DHAVE_CONFIG_H)
endif()


if(WIN32)
SET(GLOG_LIB libglog)
add_definitions(-DUNICODE -D_UNICODE -DPLATFORM_WIN32 -DOS_WIN -DCOMPILER_MSVC -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS -DHAVE_CONFIG_H)
endif()

CHECK_INCLUDE_FILE_CXX(thread HAVE_CPP_THREAD_H)
CHECK_INCLUDE_FILES(endian.h HAVE_ENDIAN_H)
CHECK_INCLUDE_FILES(sys/endian.h HAVE_SYS_ENDIAN_H)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

ADD_SUBDIRECTORY(gtest)
ADD_SUBDIRECTORY(smhash)
ADD_SUBDIRECTORY(src)
