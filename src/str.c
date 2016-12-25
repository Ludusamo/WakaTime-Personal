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

struct string *string_from_char_arr(char *str) {
    struct string *s = malloc(sizeof(struct string));
    s->len = strlen(str);
    s->ptr = malloc(s->len);
    sprintf(s->ptr, "%s", str);
    return s;
}

void string_concat(struct string *s1, struct string *s2) {
    size_t new_len = s1->len + s2->len;
    s1->len = new_len;
    sprintf(s1->ptr, "%s%s", s1->ptr, s2->ptr);
}

void deinit_string(struct string *s) {
    s->len = 0;
    free(s->ptr);
    free(s);
}
