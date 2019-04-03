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

void
usage(char *argv[])
{
	fprintf(stderr, "Usage: %s <file> [filter] [options]\n\n", argv[0]);
	fprintf(stderr, "Options:\n\t-p\tprint only items and prepend absolute path to the name.\n\n");
	fprintf(stderr, "Filters:\n\t-a <artist>\tfilter albums and songs from artist.\n");
	fprintf(stderr, "\t-g <genre>\tfilter subgenres, albums and songs from genre.\n");
	fprintf(stderr, "\t-s <string>\tfilter songs containing string (non-case-sensitive)\n");
}

filter_t
get_filter(int argc, char *argv[])
{
	int opt = 0;
	filter_t fil;

	while ((opt = getopt(argc, argv, "a:g:l:s:ph")) != -1) {
		switch (opt) {
		case 'a':
			fil = artist;
			(void) getset_artist(strdup(optarg));
			(void) getset_filter(artist);
			break;
		case 'g':
			fil = genre;
			(void) getset_genre(strdup(optarg));
			(void) getset_filter(genre);
			break;
		case 'l':
			(void) getset_album(strdup(optarg));
			(void) getset_filter(album);
			fil = album;
			break;
		case 's':
			fil = song;
			(void) getset_song(strdup(optarg));
			(void) getset_filter(song);
			break;
		case 'p':
			(void) is_playlist(yes);
			break;
		case 'h':
			usage(argv);
			exit(EXIT_SUCCESS);
		default:
			usage(argv);
			exit(EXIT_FAILURE);
		}
	}
	return fil;
}

int
main(int argc, char *argv[])
{
	filter_t fil = get_filter(argc, argv);
	string *dir = new_string(0x0);

	if (argc == 1)
		dir->append("./", dir);
	else
		dir->append(argv[argc - 1], dir);
	mtree(dir, fil);
	return 0;
}
