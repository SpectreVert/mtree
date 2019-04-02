#include "main.h"

size_t my_strlen(const char *str)
{
	register const char *s;

	for (s = str; *s; s++);
	return s - str;
}
