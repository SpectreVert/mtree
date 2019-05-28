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

char **
load_extensions(char *fname)
{
    char **exts = 0x0;
    char *buf = 0x0;
    int fd = open(fname, O_RDONLY);
    size_t ext_count = 0;
        
    if (fd == -1) {
        fprintf(stderr, "error: could not open configuration file\n");
        perror(fname);
        exit(1);
    }
    exts = malloc(sizeof(char *));
    exts[0] = 0x0;
    while ((buf = get_next_line(fd))) {
        exts[ext_count] = buf;
        ext_count++;
        exts = realloc(exts, (ext_count + 1) * sizeof(char *));
        exts[ext_count] = 0x0;
    }
    close(fd);
    if (exts[0])
        return exts;
    fprintf(stderr, "warning: no extension file preference found\n");
    fprintf(stderr, "wraning: no extension will be filtered\n");
    return exts;
}

bool
in_extensions(char *fname)
{
    static char **exts = 0x0;
    char *fext = strrchr(fname, '.');

    if (!exts)
        exts = load_extensions(EXT_FILE);
    if (!exts[0])
        return true;
    else if (!fext)
        return false;
    for (size_t index = 0; exts[index]; index++) {
        if (strcmp(fext + 1, exts[index]) == 0)
            return true;
    }
    return false;
}
