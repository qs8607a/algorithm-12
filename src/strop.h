#pragma once

namespace slib{
  size_t strlen(const char *s);
  /**
   *  locate a substring
   *  \return  These functions return a pointer to the beginning of the substring, or NULL if the substring is not found.
   */
  char * strstr(const char *s, const char *find);
  int strncmp(const char *s1, const char *s2, size_t n) ;
}
