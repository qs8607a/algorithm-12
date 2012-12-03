/*-----------------------------------------------------------------------------
 * MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain.
 *
 * This implementation was written by Shane Day, and is also public domain.
 *
 * This is a portable ANSI C implementation of MurmurHash3_x86_32 (Murmur3A)
 * with support for progressive processing.
 */

/* ------------------------------------------------------------------------- */
/* Determine what native type to use for uint32_t */

/* We can't use the name 'uint32_t' here because it will conflict with
 * any version provided by the system headers or application. */

#include <stdint.h>
#define MH_UINT32 uint32_t
/* I'm yet to work on a platform where 'unsigned char' is not 8 bits */
#define MH_UINT8  unsigned char


/* ------------------------------------------------------------------------- */
/* Prototypes */

#ifdef __cplusplus
extern "C" {
#endif

void PMurHash32_Process(uint32_t *ph1, uint32_t *pcarry, const void *key, int len);
uint32_t PMurHash32_Result(uint32_t h1, uint32_t carry, uint32_t total_length);
uint32_t PMurHash32(uint32_t seed, const void *key, int len);

void PMurHash32_test(const void *key, int len, uint32_t seed, void *out);

#ifdef __cplusplus
}
#endif
