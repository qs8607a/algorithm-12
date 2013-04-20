
/*
 * TASLock.cpp
 *
 *  Created on: Mar 5, 2010
 *      Author: Changming Sun
 */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include "TTASLock.h"
    namespace slib {

TTASLock::TTASLock() { state = tbb::make_atomic<bool>(false); }

void TTASLock::lock() {
  while (true) {
    while (state.load()) {
    }
    if (!state.fetch_and_store(true))
      return;
  }
}

bool TTASLock::try_lock() {
  //not impl
  return false;
}

void TTASLock::unlock() { state.store(false); }

}
