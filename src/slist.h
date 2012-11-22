#pragma once

#include <stdlib.h>

namespace slib{
  template <typename T>
  class ListHead{
  public:
	T* first;
	ListHead():first(NULL){}
  };
  
  template <typename T>
  class ListEntry{
	T* next;
	T** prev;
  };
  
};