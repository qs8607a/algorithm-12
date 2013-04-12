#pragma once

#include <sys/types.h>

namespace slib{
  /**
   * calculate the length of a string
   * \param s
   * \return the number of characters in s.
   */
  size_t strlen(const char *s) ;
    
  /**
   *  locate a substring
   *  \return  These functions return a pointer to the beginning of the substring, or NULL if the substring is not found.
   */
  char * strstr(const char *s, const char *find) ;
  
  int strncmp(const char *s1, const char *s2, size_t n) ;
  
  /**
   * append a copy of the null-terminated string s2 to the end of the null-termi-
   * nated string s1, then add a terminating `\0'.
   */
  char *strcat(char *  s, const char *  append);
  
  char *strdup(const char *str);
  char *strcpy(char *  to, const char *  from);
  
/*
* Copy src to dst, truncating or null-padding to always copy n bytes.
* Return dst.
*/
char *strncpy(char *  dst, const char *  src, size_t n);
	
/*
* Copy src to string dst of size siz.  At most siz-1 characters
* will be copied.  Always NUL terminates (unless siz == 0).
* Returns strlen(src); if retval >= siz, truncation occurred.
*/
size_t	strlcpy(char *  dst, const char *  src, size_t siz);

void *bsearch(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
}
