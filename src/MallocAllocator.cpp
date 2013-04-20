/*
 * MallocAllocator.cpp
 *
 *  Created on: Mar 7, 2010
 *      Author: Changming Sun
 */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include "MallocAllocator.h"
#include <cstdlib>
namespace slib {
MallocAllocator::MallocAllocator() {}

MallocAllocator::~MallocAllocator() {}

void MallocAllocator::free(void *ptr) { std::free(ptr); }

void *MallocAllocator::malloc(size_type nbytes) { return std::malloc(nbytes); }

void *MallocAllocator::calloc(size_type nmemb, size_type size) {
  return std::calloc(nmemb, size);
}

void *MallocAllocator::realloc(void *ptr, size_type size) {
  return std::realloc(ptr, size);
}

}
