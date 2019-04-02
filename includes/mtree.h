#pragma once

#define _XOPEN_SOURCE 700

#include "obj_string.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ftw.h>
#include <stdint.h>
#include <ctype.h>

#ifndef	MAX_FDS/* Maximum number of open file descriptors */
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
void tabfree(char **tab);
char *escape_char(char *s, char escape);
