/*
** EPITECH PROJECT, 2018
** obj_string.h
** File description:
** Header of string package for obj lib
*/

#include <stdlib.h>
#include <string.h>

typedef struct string_t {
	char *chars;
	void (*append)(char *, struct string_t *);
	void (*replace)(char const *, struct string_t *);
	void (*swap)(char *, struct string_t *);
	void (*pop_back)(struct string_t *);
	void (*push_back)(char, struct string_t *);
	void (*copy)(char *, struct string_t *);
	char *(*duplicate)(struct string_t *);
	void (*clear)(struct string_t *);
	size_t (*length)(struct string_t *);
} string;

string *new_string(const char *chars);
void destroy_string(string *old);

extern void *my_memcpy(void *dest, const void *src, size_t len);
extern char *my_strdup(const char *src);
extern size_t my_strlen(const char *str);
