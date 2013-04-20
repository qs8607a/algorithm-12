
#pragma once

#include "port.h"
    namespace slib {
class CountDownLatch {
private:
	int value;
	port::Mutex m;
	port::CondVar cond;
public:
	CountDownLatch(int v) : value(v) {}
	void countDown() {
		m.lock();
		try {
			if (value > 0) {
			value--;
			if (value == 0)
				cond.SignalAll();
			}
		}
  catch (...) {
		  m.unlock();
		  throw;
		}
		m.unlock();
	}
	
	void await() {
		
		m.lock();
		try {
		  while (value > 0) {
			cond.Wait();
		   }
		}
  catch (...) {
		  m.unlock();
		  throw;
		}
		m.unlock();
		}
	}
}
}
;