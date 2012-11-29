#pragma once

#include "LockInterface.h"

#include <tbb/atomic.h>

namespace slib{
class TTASLock: public LockInterface{
public:
	TTASLock();
	virtual void  lock () ;
	virtual bool  try_lock () ;
	virtual void  unlock () ; 
private:
	tbb::atomic<bool> state;
};
}
