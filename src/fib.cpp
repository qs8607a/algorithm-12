#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <algorithm>

#include "fib.h"

namespace slib{
    /**
     * 以非递归的方式计算fib数列。
     */
    int fib(int n){
        if(n<=2) return 1;
        else{
            int a(1),b(1);
            for(int i=2;i!=n;++i){
                b+=a;
                std::swap(a,b);
            }
            return a;
        }
    }
}


