#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str.h"

struct string {
	char *ptr;
	size_t len;
};

void init_string(struct string *s);
struct string *string_from_char_arr(char *str);
void string_concat(struct string *s1, struct string *s2);
void deinit_string(struct string *s);


#endif // STRING_H
