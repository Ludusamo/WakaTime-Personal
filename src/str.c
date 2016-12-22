#include "str.h"

void init_string(struct string *s) {
	s->len = 0;
	s->ptr = malloc(s->len + 1);
	if (s->ptr == NULL) {
		fprintf(stderr, "malloc() failed to allocate string\n");
		exit(EXIT_FAILURE);
	}
	s->ptr[0] = '\0';
}

void deinit_string(struct string *s) {
    s->len = 0;
    free(s->ptr);
    free(s);
}
