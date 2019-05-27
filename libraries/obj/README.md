# libobj

Base for a small C library implementing cpp-like strings with a "few" methods.

Next version will have template arrays.

### String API

Yes, for each and every method you'll have to use the string object itself as the first parameter. Still beats getting 
segfaults because of a non null-terminated string.

`string *new_string(char const *s)`

__Brief:__ Allocate a new string object and set it to a duplicate of _s_

__Return:__ a pointer to the new string object

`void destroy_string(string *s)`

__Brief:__ Release all data linked to the string object

### Member functions

The following functions are accessible as methods. I.e:

```
string *s = new_string("github");

s->func(s, ...);
```

`char *at(string *self, size_t n)`

__Brief:__ Return a pointer to the _n_ th character

__Return__: A pointer to the _n_ th character of the string

If _n_ is out of bounds of the string, NULL is returned

`void upper(string *self)`

__Brief:__ Convert lowercase to uppercase.

`void lower(string *self)`

__Brief:__ Convert uppercase to lowercase.

`void append(string *self, const char *s)`

__Brief:__ Append _s_ to the string

`void prepend(string *self, const char *s)`

__Brief:__ Prepend _s_ to the string

`void set(string *self, const char *s)`

__Brief:__ Set the string to a copy of _s_

`char *swap(string *self, string *s)`

__Brief:__ Swap string with _s_

`char pop_back(string *self)`

__Brief:__ Remove the last character of the string

__Return:__ The removed character

`void push_back(string *self, char c)`

__Brief__: Append _c_ to the string

`char pop_front(string *self)`

__Brief:__ Remove the first character of the string

__Return:__ The removed character

`void push_front(string *self, char c)`

__Brief:__ Prepend _c_ to the string

`char *find(string *self, const char *needle)`

__Brief:__ Find the first occurence of _needle_ in the string

__Return:__ A pointer to the position of the found substring or NULL if not found

`void map(string *self, char (*lambda)(char c))`

__Brief:__ Apply _lambda_ to each character of the string

`string *duplicate(string *self)`

__Brief:__ Copy the string

__Return:__ A pointer to a copy of the string

`void clear(string *self)`

__Brief:__ Clear the string

`size_t len(string *self)`

__Brief:__ Get the length of the string

__Return:__ The length of the string

`char *get(string *self)`

__Brief:__ Get access to the internal char * of the string

__Return:__ A pointer to the internal char * of the string

`void puts(string *self)`

__Brief:__ Print the string to standard output followed by a line-feed

`size_t size(string *self)`

__Brief:__ Get the number of bytes used for the string's storage

__Return:__ Return the number of bytes used for the string's storage

`void destroy(string *self)`

__Brief:__ Release all data linked to the string object
