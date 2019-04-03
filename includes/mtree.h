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

typedef enum things_s {
	add_folder,
	add_file,
	query_artist,
	query_genre,
	query_album,
	query_song,
} things_t;

typedef enum filter_s {
	NONE,
	artist,
	album,
	genre,	
	song
} filter_t;

typedef enum playlist_s {
	get,
	yes,
	no
} playlist_t;

void mtree(string *dir, filter_t fil);
bool is_upper(char c);
bool is_lower(char c);
bool is_num(char c);
char *getset_artist(char *s);
char *getset_genre(char *s);
char *getset_song(char *s);
char *getset_album(char *s);
playlist_t is_playlist(playlist_t p);
filter_t getset_filter(filter_t f);
char **strtotab(char *s, char tok);
void puttab(char **tab);
size_t tablen(char **tab);
size_t get_level(char *base_name, char **tab);
void tabfree(char **tab);
bool strintab(const char *s, char **tab);
char *escape_char(char *s, char escape);
