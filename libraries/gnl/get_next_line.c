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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef READ_SIZE
#define READ_SIZE 10
#endif


/* 
** This function can be replaced by a trivial realloc.
*/

char *resize_buffer(char *buffer, int size, int pos)
{
        char *tmp = malloc(size);
        int c = 0;

        if (tmp == 0x0)
                return 0x0;
        while (c != pos) {
                tmp[c] = buffer[c];
                c++;
        }
        tmp[c] = 0;
        free(buffer);
        return tmp;
}

char get_next_char(int fd)
{
        static char buffer[READ_SIZE];
        static int offset = 0;
        static char *buffer_cpy = 0x0;
        char next;

        if (offset == 0) {
                offset = read(fd, buffer, READ_SIZE);
                buffer_cpy = (char *) &buffer;
                if (offset == 0)
                        return 0;
        }
        offset--;
        return *buffer_cpy++;
}

char *get_next_line(int fd)
{
        char *buffer = malloc(READ_SIZE + 1);
        char next;
        int pos = 0;

        if (buffer == 0x0)
                return 0x0;
        next = get_next_char(fd);
        while (next != 0 && next != '\n') {
                buffer[pos] = next;
                pos++;
                next = get_next_char(fd);
                if (pos % READ_SIZE == 0)
                        buffer = resize_buffer(buffer, pos + READ_SIZE, pos);
        }
        buffer[pos] = 0;
        if (buffer[0] == 0 && next == 0)
                return 0x0;
        return buffer;
}
