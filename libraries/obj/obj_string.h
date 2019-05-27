/*
    Copyright (C) 2019 Costa Bushnaq -> SpectreVert@github.com

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

#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct string_t {
	char *chars;
	bool def;
	char *(*at)(struct string_t *self, size_t);
	void (*upper)(struct string_t *self);
	void (*lower)(struct string_t *self);
	void (*append)(struct string_t *self, const char *s);
	void (*prepend)(struct string_t *self, const char *s);
	void (*set)(struct string_t *self, const char *s);
	void (*swap)(struct string_t *, struct string_t *);
	char (*pop_back)(struct string_t *);
	void (*push_back)(struct string_t *, char c);
	char (*pop_front)(struct string_t *);
	void (*push_front)(struct string_t *, char c);
	char *(*find)(struct string_t *, const char *);
	void (*map)(struct string_t *, char (*)(char));
	struct string_t *(*duplicate)(struct string_t *);
	void (*clear)(struct string_t *);
	size_t (*len)(struct string_t *);
	char *(*get)(struct string_t *);
	void (*puts)(struct string_t *);
	size_t (*size)(struct string_t *t);
	void (*destroy)(struct string_t *t);
} string;

string *new_string(char *chars);
void destroy_string(string *old);
