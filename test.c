#include <stdio.h>

int main(int ac, char *av[])
{
	for (unsigned i = 0; av[i]; ++i) {
		puts(av[i]);
	}
}
