/*
 * Allocator.h
 *
 *  Created on: Mar 7, 2010
 *      Author: Changming Sun
 */

#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

namespace slib {
template <typename sizeT> class Allocator {
 public:
  typedef sizeT size_type;
  Allocator() {}
  virtual ~Allocator() {}

  /**
 	 * @param size_type 分配多少内存
 	 */
  virtual void *malloc(size_type nbytes) = 0;
  virtual void free(void *ptr) = 0;
  virtual void *calloc(size_type nmemb, size_type size) = 0;
  virtual void *realloc(void *ptr, size_type size) = 0;

};
}

#endif /* ALLOCATOR_H_ */
