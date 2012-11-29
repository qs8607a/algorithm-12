#pragma once

namespace slib{
class LockInterface{
	virtual void  lock () = 0;
	virtual bool  try_lock () = 0;
	virtual void  unlock () = 0; 
};
}