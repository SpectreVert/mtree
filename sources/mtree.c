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

inline bool
is_upper(char c)
{
	return (c > 64 && c < 91);
}

inline bool
is_lower(char c)
{
	return (c > 97 && c < 123);
}

inline bool
is_num(char c)
{
	return (c >= '0' && c <= '9');
}

char *
to_upper(char *s)
{
	for (unsigned i = 0; s[i]; ++i)
		s[i] = toupper(s[i]);
	return s;
}

playlist_t
is_playlist(playlist_t p)
{
	static playlist_t playlist = no;

	if (p != get)
		playlist = p;
	return playlist;
}

filter_t
getset_filter(filter_t f)
{
	static filter_t filter = NONE;

	if (f != NONE)
		filter = f;
	return filter;
}

inline char *
getset_artist(char *s)
{
	static char *n = 0x0;

	if (s != 0x0)
		n = s;
	return n;
}

inline char *
getset_genre(char *s)
{
	static char *n = 0x0;

	if (s != 0x0)
		n = s;
	return n;
}

inline char *
getset_album(char *s)
{
	static char *n = 0x0;

	if (s != 0x0)
		n = s;
	return n;
}

inline char *
getset_song(char *s)
{
	static char *n = 0x0;

	if (s != 0x0)
		n = s;
	return n;
}

uint64_t
count_things(const char *fname, things_t mode)
{
	static uint64_t artists = 0;
	static uint64_t genres = 0;
	static uint64_t albums = 0;
	static uint64_t songs = 0;

	switch (mode) {
	case add_file:
		songs++;
		break;
	case add_folder:
		if (is_lower(fname[0]))
			genres++;
		else if (is_upper(fname[0]))
			artists++;
		else if (is_num(fname[0]))
			albums++;
		break;
	case query_song:
		return songs;
	case query_genre:
		return genres;
	case query_artist:
		return artists;
	case query_album:
		return albums;
	}
	return 0;
}

void
print_branches(struct FTW *ftwbuf)
{
	static int lev = 0;

	if (lev < ftwbuf->level)
		lev++;
	else if (lev > ftwbuf->level)
		lev = ftwbuf->level;
	for (int i = 0; i != lev; i++) {
		if (i == lev - 1)
			fprintf(stdout, "`--- ");
		else
			fprintf(stdout, "     ");
	}
}

void
print_lonely_branches(size_t level)
{
	for (size_t i = 0; i != level; ++i)
		fprintf(stdout, "     ");
	fprintf(stdout, "`--- ");
}

/* Unused for now. Still there in case I'll make symlinks items possible. */
void
print_symlink(const char *fpath, struct FTW *ftwbuf)
{
	string *fname = new_string(fpath);
	char *buf = 0x0;
	size_t buflen = 255;
	ssize_t len = 0;

	print_branches(ftwbuf);
	while (1) {
		buf = malloc(buflen + 1);
		len = readlink(fpath, buf, buflen);
		if (len == (ssize_t) -1) {
			free(buf);
			destroy_string(fname);
			return;
		}
		if (len >= (ssize_t) buflen) {
			free(buf);
			destroy_string(fname);
			buflen += 256;
			continue;
		}
		buf[len] = 0;
		break;
	}
	if (is_playlist(get) == no)
		fprintf(stdout, "%s -> %s\n", fname->chars + ftwbuf->base, buf);
	free(buf);
	destroy_string(fname);
}

void
print_file_artist(string *fname, struct FTW *ftwbuf)
{
	char **fpath = 0x0;

	if (strstr(fname->chars, getset_artist(0x0)) != 0x0) {
		if (is_playlist(get) == no) {
			fpath = strtotab(fname->chars, '/');
			count_things(fname->chars + ftwbuf->base, add_file);
			print_lonely_branches(get_level(getset_artist(0x0), fpath));
			fprintf(stdout, "%s\n", fname->chars + ftwbuf->base);
		} else
			fprintf(stdout, "%s ", fname->chars);
	}
}

void
print_file_song(string *fname, struct FTW *ftwbuf)
{
	string *tmp = new_string(fname->chars + ftwbuf->base);
	string *tmp2 = new_string(getset_song(0x0));
	char **path_tab = 0x0;

	if (strstr(to_upper(tmp->chars), to_upper(tmp2->chars)) != 0x0
	&& is_playlist(get) == no) {
		count_things(fname->chars + ftwbuf->base, add_file);
		fprintf(stdout, "%s", fname->chars + ftwbuf->base);
		path_tab = strtotab(fname->chars, '/');
		if (tablen(path_tab) >= 1) {
			fprintf(stdout, " by %s [%s]",
			path_tab[tablen(path_tab) - 3],
			path_tab[tablen(path_tab) - 2]);
		}
		puts("");
		tabfree(path_tab);
	} else if (strstr(to_upper(tmp->chars), to_upper(tmp2->chars)) != 0x0
	&& is_playlist(get) == yes) {
		fname->chars = escape_char(fname->chars, 32);
		fprintf(stdout, "%s ", fname->chars);
	}
	destroy_string(tmp);
	destroy_string(tmp2);
}

void
print_file_genre(string *fname, struct FTW *ftwbuf)
{
	char **fpath = 0x0;

	if (is_playlist(get) == no) {
		fpath = strtotab(fname->chars, '/');
		if (strintab(getset_genre(0x0), fpath)) {
			count_things(fname->chars + ftwbuf->base, add_file);
			print_lonely_branches(get_level(getset_genre(0x0), fpath));
			fprintf(stdout, "%s\n", fname->chars + ftwbuf->base);
		}
		tabfree(fpath);
	} else
		fprintf(stdout, "%s ", fname->chars);
}

void
print_file_none(string *fname, struct FTW *ftwbuf)
{
	if (is_playlist(get) == no) {
		count_things(fname->chars + ftwbuf->base, add_file);
		print_branches(ftwbuf);
		fprintf(stdout, "%s\n", fname->chars + ftwbuf->base);
	} else
		fprintf(stdout, "%s ", fname->chars);
}

void
print_file(string *fname, struct FTW *ftwbuf)
{
	switch (getset_filter(NONE)) {
	case artist:
		print_file_artist(fname, ftwbuf);
		break;
	case genre:
		print_file_genre(fname, ftwbuf);
		break;
	case album:
		break;
	case song:
		print_file_song(fname, ftwbuf);
		break;
	case NONE:
		print_file_none(fname, ftwbuf);
		break;
	}
}

void
print_folder_artist(string *fname, struct FTW *ftwbuf)
{
	char **fpath = 0x0;

	if (is_playlist(get) != no)
		return;
	if (strcmp(getset_artist(0x0), fname->chars + ftwbuf->base) == 0)
		fprintf(stdout, "%s/\n", fname->chars + ftwbuf->base);
	else {
		fpath = strtotab(fname->chars, '/');
		if (strintab(getset_artist(0x0), fpath)) {
			count_things(fname->chars + ftwbuf->base, add_folder);
			print_lonely_branches(get_level(getset_artist(0x0), fpath));
			fprintf(stdout, "%s/\n", fname->chars + ftwbuf->base);
		}
		tabfree(fpath);
	}
}

void
print_folder_genre(string *fname, struct FTW *ftwbuf)
{
	char **fpath = 0x0;

	if (is_playlist(get) != no)
		return;
	if (strcmp(getset_genre(0x0), fname->chars + ftwbuf->base) == 0)
		fprintf(stdout, "%s/\n", fname->chars + ftwbuf->base);
	else {
		fpath = strtotab(fname->chars, '/');
		if (strintab(getset_genre(0x0), fpath)) {
			count_things(fname->chars + ftwbuf->base, add_folder);
			print_lonely_branches(get_level(getset_genre(0x0), fpath));
			fprintf(stdout, "%s/\n", fname->chars + ftwbuf->base);
		}
		tabfree(fpath);
	}
}

void
print_folder_none(string *fname, struct FTW *ftwbuf)
{
	count_things(fname->chars + ftwbuf->base, add_folder);
	print_branches(ftwbuf);
	fprintf(stdout, "%s/\n", fname->chars + ftwbuf->base);
}

void
print_folder(string *fname, struct FTW *ftwbuf)
{
	if (is_playlist(get) == yes)
		return;
	switch (getset_filter(NONE)) {
	case artist:
		print_folder_artist(fname, ftwbuf);
		break;
	case genre:
		print_folder_genre(fname, ftwbuf);
		break;
	case album:
		break;
	case song:
		break;
	case NONE:
		print_folder_none(fname, ftwbuf);
		break;
	}
}

void
print_things(const char *fpath, int flag, struct FTW *ftwbuf)
{
	string *fname = new_string(fpath);

	if (flag == FTW_SL)
		(void) fname;
		/* print_symlink(fname->chars, ftwbuf); */
	else if (flag == FTW_F)
		print_file(fname, ftwbuf);
	else if (flag == FTW_D || flag == FTW_DP || flag == FTW_DNR)
		print_folder(fname, ftwbuf);
	destroy_string(fname);
}

void
print_result_artist(void)
{
	fprintf(stdout, "artist: %s\n\n", getset_artist(0x0));
	fprintf(stdout, "songs: %zd\n", count_things(0x0, query_song));
	fprintf(stdout, "albums: %zd\n", count_things(0x0, query_album));
}

void
print_result_genre(void)
{
	fprintf(stdout, "genre: %s\n\n", getset_genre(0x0));
	fprintf(stdout, "subgenres: %zd\n", count_things(0x0, query_genre));
	fprintf(stdout, "artists: %zd\t", count_things(0x0, query_artist));
	fprintf(stdout, "albums: %zd\n", count_things(0x0, query_album));
}

void
print_result_song(void)
{
	fprintf(stdout, "songs: %zd\n", count_things(0x0, query_song));
}

void
print_result_none(void)
{
	fprintf(stdout, "songs: %zd\t", count_things(0x0, query_song));
	fprintf(stdout, "artists: %zd\n", count_things(0x0, query_artist));
	fprintf(stdout, "albums: %zd\t", count_things(0x0, query_album));
	fprintf(stdout, "genres: %zd\n", count_things(0x0, query_genre));
}

void
print_result(void)
{
	if (is_playlist(get) == yes)
		return;
	write(1, "\n", 1);
	switch (getset_filter(NONE)) {
		case artist:
			print_result_artist();
			break;
		case genre:
			print_result_genre();
			break;
		case album:
			break;
		case song:
			print_result_song();
			break;
		case NONE:
			print_result_none();
			break;
	}
}

int
print_mtree(const char *fpath, const struct stat *sb, int flag, struct FTW *ftwbuf)
{
	(void) sb;
	print_things(fpath, flag, ftwbuf);
	return 0;
}

void
mtree(string *dir, filter_t fil)
{
	(void) fil;
	(void) nftw(dir->chars, print_mtree, MAX_FDS, FTW_PHYS);
	print_result();
	destroy_string(dir);
}
