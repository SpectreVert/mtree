#include "main.h"

char *my_strdup(const char *src)
{
	char *dest = malloc(sizeof(*dest) * (my_strlen(src) + 1));

	return my_memcpy((char *) dest, (char *) src, my_strlen(src) + 1);
}
