﻿
#pragma once

#include "LockInterface.h"

#include <tbb/atomic.h>
    namespace slib {
  class TASLock : public LockInterface {
   public:
    TASLock();
    virtual void lock();
    virtual bool try_lock();
    virtual void unlock();

   private:
    tbb::atomic<bool> state;
  };
}
