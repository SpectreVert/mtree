#include "mtree.h"

void
usage(char *argv[])
{
	fprintf(stderr, "Usage: %s [FILE] [-a|-g|-l]\n", argv[0]);
}

filter_t
get_filter(int argc, char *argv[])
{
	int opt = 0;
	filter_t fil;

	while ((opt = getopt(argc, argv, "a:g:l:s:p")) != -1) {
		switch (opt) {
		case 'a':
			fil = artist;
			(void) getset_artist(strdup(optarg));
			(void) getset_filter(artist);
			break;
		case 'g':
			fil = genre;
			break;
		case 'l':
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
