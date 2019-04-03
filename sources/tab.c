/*
    Copyright (C) 2019 SpectreVert@github.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "mtree.h"

unsigned int
number_of(char *s, char tok)
{
	unsigned int c = 0;

	for (const char *i = s; *i; ++i)
		if (*i == tok)
			++c;
	return c;
}

/* Careful! frees up the char *s */
char *
escape_char(char *s, char escape)
{
	char *new = malloc(strlen(s) + number_of(s, escape) + 1);
	unsigned int c = 0;

	for (unsigned int i = 0; s[i]; ++i) {
		if (s[i] == escape) {
			new[c] = '\\';
			c++;
		}
		new[c] = s[i];
		c++;
	}
	free(s);
	new[c] = '\0';
	return new;
}

size_t
tablen(char **tab)
{
	size_t i = 0;

	for (; tab[i]; ++i);
	return i;
}

size_t
get_level(char *base_name, char **tab)
{
	size_t len = tablen(tab);
	size_t i = len - 1;

	for (; i > 0 && strcmp(tab[i], base_name) != 0; --i);
	return len - i - 2;
}

char **
strtotab(char *s, char tok)
{
	char **r = malloc(sizeof(char *) * (number_of(s, tok) + 2));
	unsigned int t1 = 0;
	unsigned int t2 = 0;

	r[t1] = malloc(strlen(s) + 1);
	for (unsigned int i = 0; s[i]; ++i) {
		if (s[i] == tok) {
			r[t1][t2] = '\0';
			++t1;
			t2 = 0;
			r[t1] = malloc(strlen(s) + 1);
		} else
			r[t1][t2++] = s[i];
	}
	r[t1][t2] = '\0';;
	r[t1 + 1] = 0x0;
	return r;
}

bool
strintab(const char *s, char **tab)
{
	for (unsigned int i = 0; tab[i]; ++i)
		if (strcmp(tab[i], s) == 0)
			return true;
	return false;
}

void
puttab(char **tab)
{
	for (unsigned int i = 0; tab[i]; ++i)
		puts(tab[i]);
}

void
tabfree(char **tab)
{
	for (unsigned int i = 0; tab[i]; ++i)
		free(tab[i]);
}
