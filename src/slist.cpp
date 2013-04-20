
#if HAVE_CONFIG_H
#include <config.h>
#endif

#include "slist.h"
    namespace slib {
  ListHead ListHead::shared_null = { &ListHead::shared_null,
                                     &ListHead::shared_null,
                                     tbb::make_atomic(1), true, true };
}