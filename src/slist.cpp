#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "slist.h"

namespace slib{
	ListHead ListHead::shared_null = {
		&ListHead::shared_null, &ListHead::shared_null,
		ATOMIC_VAR_INIT(1), 0, true
	};
}