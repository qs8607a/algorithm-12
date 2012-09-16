#pragma once
#include "stddef.h"

namespace slib {

/**
 * malloc/free
 */
class MallocAllocator {
public:
	typedef size_t size_type;
	MallocAllocator();
	virtual ~MallocAllocator();
	static  void *malloc(size_type nbytes) ;
	static  void free(void *ptr) ;
	static  void *calloc(size_type nmemb, size_type size);
	static  void *realloc(void *ptr, size_type size);
};
}

