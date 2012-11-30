#if HAVE_CONFIG_H
# include <config.h>
#endif

#include "TASLock.h"

namespace slib{

	TASLock::TASLock(){
		state=tbb::make_atomic<bool>(false);
	}

	void TASLock::lock(){
		while(state.fetch_and_store(true)){}
	}

	bool TASLock::try_lock(){
		//not impl
		return false;
	}

	void TASLock::unlock(){
		state.store(false);
	}

}

