#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "string.h"

namespace slib{
  size_t strlen(const char *s){
    if(s==NULL) return 0;
    size_t ret=0;
    while(*s++ != '\0')
      ret++;
    return ret;
  }


  int strncmp(const char *s1, const char *s2, size_t n) {
    if (n == 0)
      return (0);
    do {
      if (*s1 != *s2++)
	return (*(const unsigned char *)s1 -
		*(const unsigned char *)(s2 - 1));
      if (*s1++ == '\0')
	break;
    } while (--n != 0);
    return (0);
  }

  char * strstr(const char *s, const char *find) {
    char c, sc;
    size_t len;

    if ((c = *find++) != '\0') {
      len = strlen(find);
      do {
	do {
	  if ((sc = *s++) == '\0')
	    return (NULL);
	} while (sc != c);
      } while (strncmp(s, find, len) != 0);
      s--;
    }
    return ((char *)s);
  }
}
