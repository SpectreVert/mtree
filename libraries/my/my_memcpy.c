#include "main.h"

void *my_memcpy(void *dest, const void *src, size_t len)
{
	const char *s = src;
	char *d = dest;

	while (len--)
		*d++ = *s++;
	return dest;
}
