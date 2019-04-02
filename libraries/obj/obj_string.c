#include "obj_string.h"

void obj_string_append(char *app, string *self)
{
	char *new;

	new = malloc(sizeof(*new) * (my_strlen(self->chars) + my_strlen(app) + 2));
	new[0] = 0;
	new = strcat(new, self->chars);
	new = strcat(new, app);
	free(self->chars);
	self->chars = new;
}

void obj_string_replace(char const *rep, string *self)
{
	free(self->chars);
	self->chars = my_strdup(rep);
}

void obj_string_swap(char *swap, string *self)
{
	char *temp = self->chars;

	self->chars = swap;
	swap = temp;	
}

void obj_string_pop_back(string *self)
{	
	char *new;

	if (self->chars[0] == 0)
		return;
	new = malloc(sizeof(*new) * my_strlen(self->chars));
	new = my_memcpy((char *) new, (char *) self->chars, my_strlen(self->chars));
	new[my_strlen(self->chars) - 1] = 0;
	free(self->chars);
	self->chars = new;
}

void obj_string_push_back(char to_push, string *self)
{
	char *new;

	new = malloc(sizeof(*new) * (my_strlen(self->chars) + 2));
	new = my_memcpy((char *) new, (char *) self->chars, my_strlen(self->chars) + 1);
	new[my_strlen(self->chars)] = to_push;
	new[my_strlen(self->chars) + 1] = 0;
	free(self->chars);
	self->chars = new;
}

char *obj_string_duplicate(string *self)
{
	char *dest;

	dest = malloc(sizeof(char) * (my_strlen(self->chars) + 1));
	dest = my_memcpy((char *) dest, (char *) self->chars, my_strlen(self->chars) + 1);
	return dest;
}

void obj_string_clear(string *self)
{
	char *empty;

	free(self->chars);
	empty = malloc(sizeof(char));
	empty[0] = 0;
	self->chars = empty;
}

size_t obj_string_length(string *self)
{
	return my_strlen(self->chars);
}

string *new_string(const char *chars)
{
	string *new = malloc(sizeof(*new));

	if (chars == NULL)
		new->chars = my_strdup("");
	else
		new->chars = my_strdup(chars);
	new->append = obj_string_append;
	new->replace = obj_string_replace;
	new->swap = obj_string_swap;
	new->pop_back = obj_string_pop_back;
	new->push_back = obj_string_push_back;
	new->duplicate = obj_string_duplicate;
	new->clear = obj_string_clear;
	new->length = obj_string_length;
	return new;
}

void destroy_string(string *old)
{
	free(old->chars);
	free(old);
}
