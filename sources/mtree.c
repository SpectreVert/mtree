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

#include <mtree.h>

/* Note:
** Now it's really convenient to check for extensions
** and filter out unwanted files. User adds prefered
** extensions in '.mtree' file which will be loaded
** at launch.
*/

void
assess_file(string *fname, struct FTW *ftwbuf)
{
    char *file = strrchr(fname->get(fname), '/');

    (void) ftwbuf;
    if (file && in_extensions(file + 1)) {
        fname->puts(fname);
    }
}

/* Note: 
** Contrary to previous version it is irrelevant if
** we find ourselves in a folder, the interesting
** stuff happens when we find a file: we can
** backtrace the folders using the whole filepath
** provided by nftw.
** This not only removes a lot of previously useless
** operations but also simplifies the process.
*/

int
travel_mtree(const char *fpath, const struct stat *sb, int flag, struct FTW *ftwbuf)
{
    string *fname = new_string(fpath);
    (void) sb;

    if (flag == FTW_F)
        assess_file(fname, ftwbuf);
    
    destroy_string(fname);
    return 0;
}

void
display_mtree(void)
{

}

void
mtree(string *dir, filter_t fil)
{
    (void) dir;
    (void) fil;

    dir->puts(dir);
    (void) nftw(dir->get(dir), travel_mtree, MAX_FDS, FTW_PHYS);
    display_mtree();
}
