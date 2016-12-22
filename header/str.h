#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>

struct string {
	char *ptr;
	size_t len;
};

void init_string(struct string *s);
void deinit_string(struct string *s);

#endif // STRING_H
