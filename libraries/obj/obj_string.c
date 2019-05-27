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

#include "obj_string.h"

static char *
obj_string_at(string *self, size_t pos)
{
    unsigned int c = 0;

    if (!self->def || pos <= 0 || pos > self->len(self))
        return 0x0;
    for (;self->chars[c] && c != pos; ++c);
    return self->chars + c;
}

static void
obj_string_upper(string *self)
{
    if (!self->def)
        return;
    for (char *i = self->chars; *i; *i++)
        if (*i >= 'a' && *i <= 'z')
            *i -= 32;
}

static void
obj_string_lower(string *self)
{
    if (!self->def)
        return;
    for (char *i = self->chars; *i; *i++)
        if (*i >= 'A' && *i <= 'Z')
            *i += 32;
}

static void
obj_string_append(string *self, const char *s)
{
    char *new = 0x0;

    if (!self->def) {
        self->chars = strdup(s);
        self->def = true;
    } else {
        new = malloc(strlen(self->chars) + strlen(s) + 1);
        new[0] = '\0';
        new = strcat(new, self->chars);
        new = strcat(new, s);
        free(self->chars);
    }
    self->chars = new;
}

static void
obj_string_prepend(string *self, const char *s)
{
    char *new = 0x0;

    if (!self->def) {
        self->chars = strdup(s);
        self->def = true;
    } else {
        new = malloc(strlen(self->chars) + strlen(s) + 1);
        new[0] = '\0';
        new = strcat(new, s);
        new = strcat(new, self->chars);
        free(self->chars);
    }
    self->chars = new;
}

static void
obj_string_set(string *self, const char *s)
{
    if (self->def)
        free(self->chars);
    self->chars = strdup(s);
    self->def = true;
}

static void
obj_string_swap(string *self, string *s)
{
    char *tmp = 0x0;

    if (s->def && self->def) {
        tmp = s->chars;
        s->chars = self->chars;
        self->chars = tmp;
    }
}

static char
obj_string_pop_back(string *self)
{   
    char *new = 0x0;
    char r;

    if (!self->def || self->chars[0] == '\0')
        return 0;
    new = malloc(strlen(self->chars) + 1);
    new = strcpy(new, self->chars);
    new[strlen(self->chars) - 1] = '\0';
    r = self->chars[strlen(self->chars) - 1];
    free(self->chars);
    self->chars = new;
    return r;
}

static void
obj_string_push_back(string *self, char c)
{
    char *new = 0x0;

    if (self->def) {
        new = malloc(strlen(self->chars) + 2);
        new = strcpy(new, self->chars);
        new[strlen(self->chars)] = c;
        new[strlen(self->chars) + 1] = '\0';
        free(self->chars);
    } else {
        new = malloc(2);
        new[0] = c;
        new[1] = '\0';
    } 
    self->chars = new;
    self->def = true;
}

static char
obj_string_pop_front(string *self)
{
    char *new = 0x0;
    char r;

    if (!self->def || self->chars[0] == '\0')
        return 0;
    new = malloc(strlen(self->chars));
    new = strcpy(new, self->chars + 1);
    r = self->chars[0];
    free(self->chars);
    self->chars = new;
    return r;
}

static void
obj_string_push_front(string *self, char c)
{
    char *new = 0x0;

    if (self->def) {
        new = malloc(strlen(self->chars) + 2);
        (void) strcpy(new + 1, self->chars);
        new[0] = c;
        free(self->chars);
    } else {
        new = malloc(2);
        new[0] = c;
        new[0] = '\0';
    }
    self->chars = new;
    self->def = true;
}

static char *
obj_string_find(string *self, const char *needle)
{
    if (!self->def)
        return 0x0;
    return strstr(self->chars, needle);
}

static void
obj_string_map(string *self, char (*lambda)(char c))
{
    if (!self->def)
        return;
    for (char *i = self->chars; *i; *i++)
        *i = lambda(*i);
}

static string
*obj_string_duplicate(string *self)
{
    char *s = 0x0;

    if (!self->def)
        return 0x0;
    return new_string(self->chars);
}

static void
obj_string_clear(string *self)
{
    char *empty = malloc(1);

    if (self->def)
        free(self->chars);
    empty[0] = '\0';
    self->chars = empty;
    self->def = true;
}

static size_t
obj_string_len(string *self)
{
    if (self->def)
        return strlen(self->chars);
    return 0;
}

static char *
obj_string_get(string *self)
{
    if (self->def)
        return self->chars;
    return 0x0;
}

static void
obj_string_puts(string *self)
{
    if (self->def)
        puts(self->chars);
}

static size_t
obj_string_size(string *self)
{
    return sizeof(*self);
}

static void
obj_string_destroy(string *self)
{
    if (self->def)
        free(self->chars);
    free(self);
}

string *
new_string(char *chars)
{
    string *new = malloc(sizeof(*new));

    if (chars == NULL)
        new->chars = strdup("");
    else
        new->chars = strdup(chars);
    new->def = true;
    new->at = obj_string_at;
    new->upper = obj_string_upper;
    new->lower = obj_string_lower;
    new->append = obj_string_append;
    new->prepend = obj_string_prepend;
    new->set = obj_string_set;
    new->swap = obj_string_swap;
    new->pop_back = obj_string_pop_back;
    new->push_back = obj_string_push_back;
    new->pop_front = obj_string_pop_front;
    new->push_front = obj_string_push_front;
    new->find = obj_string_find;
    new->map = obj_string_map;
    new->duplicate = obj_string_duplicate;
    new->clear = obj_string_clear;
    new->len = obj_string_len;
    new->get = obj_string_get;
    new->puts = obj_string_puts;
    new->size = obj_string_size;
    new->destroy = obj_string_destroy;
    return new;
}

void
destroy_string(string *old)
{
    if (old->def)
        free(old->chars);
    free(old);
}
