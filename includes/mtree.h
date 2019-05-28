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

#pragma once

#define _XOPEN_SOURCE 700

#include "obj_string.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ftw.h>
#include <stdint.h>
#include <ctype.h>

/* Maximum number of open file descriptors. */
#ifndef	MAX_FDS
#define MAX_FDS 15
#endif

/* Keep track of what has to be filtered for display. */
typedef struct filter_s {
	string *art;
	string *gen;
	string *alb;
	string *son;
	bool playlist;
} filter_t;

void mtree(string *dir, filter_t fil);
