#if HAVE_CONFIG_H
# include <config.h>
#endif


#include "string.h"

namespace slib{
	size_t strlen(const char *s){
		if(s==NULL) return 0;
		size_t ret=0;
		//一直找到'\0'为止
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
		size_t len;
		const char c = *find++;
		if ( c != '\0') {
			len = strlen(find);
			do {
				char  sc;
				do {
					if ((sc = *s++) == '\0')
						return (NULL);
				} while (sc != c);
			} while (strncmp(s, find, len) != 0);
			s--;
		}
		return ((char *)s);
	}

	char *strcat(char * __restrict s, const char * __restrict append){
		char * const save = s;

		//先找到s的末尾('\0'在哪）
		for (; *s; ++s);
		//然后挨个赋值
		while ((*s++ = *append++));
		return(save);
	}

	char *strdup(const char *str){
		const size_t len = strlen(str) + 1;
		char * const copy = new char[len];	        
		memcpy(copy, str, len);
		return (copy);
	}

	char *strcpy(char * __restrict to, const char * __restrict from){
		char * const save = to;

		for (; (*to = *from); ++from, ++to);
		return(save);
	}
	
	char * strncpy(char * __restrict dst, const char * __restrict src, size_t n){
		if (n != 0) {
			char *d = dst;
			const char *s = src;

			do {
				if ((*d++ = *s++) == '\0') {
					/* NUL pad the remaining n-1 bytes */
					while (--n != 0)
						*d++ = '\0';
					break;
				}
			} while (--n != 0);
		}
		return (dst);
	}

	size_t	strlcpy(char * __restrict dst, const char * __restrict src, size_t siz){
		char *d = dst;
		const char *s = src;
		size_t n = siz;

		/* Copy as many bytes as will fit */
		if (n != 0) {
			while (--n != 0) {
				if ((*d++ = *s++) == '\0')
					break;
			}
		}

		/* Not enough room in dst, add NUL and traverse rest of src */
		if (n == 0) {
			if (siz != 0)
				*d = '\0';		/* NUL-terminate dst */
			while (*s++)
				;
		}

		return(s - src - 1);	/* count does not include NUL */
	}

	
	void *bsearch(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *)){
		const char *base = (const char *)base0;						

		for (size_t lim = nmemb; lim != 0; lim >>= 1) {
			const void *p = base + (lim >> 1) * size;
			int cmp = (*compar)(key, p);
			if (cmp == 0)
				return ((void *)p);

			//下面注意要分2x2种情况讨论。左移，右移，lim偶数，lim奇数。

			if (cmp > 0) {	/* key > p: move right */
				base = (char *)p + size; //base等于中值右移一位
				lim--; //lim如果是偶数，在折半前要减少1. 如果是奇数，减不减都可以
			}		/* else move left. base不变,lim折半 */
		}
		return (NULL);
	}
}
