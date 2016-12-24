#include "filesystem.h"

void check_or_create_dir(struct string *path) {
    struct stat st = {0};

    printf("%s\n", path->ptr);
    if (stat(path->ptr, &st) == -1) {
        mkdir(path->ptr, 0700);
    }
}

struct string *get_api_key() {
    FILE *api_key_file = fopen("bin/api_key", "r");
	if (api_key_file) {
		struct string *api_key = malloc(sizeof(struct string));
		api_key->ptr = malloc(37);
		api_key->len = 37;
		fscanf(api_key_file, "%s", api_key->ptr);
        return api_key;
    } else {
		fprintf(stderr, "error: no api key file\nRerun application setup");	
        exit(EXIT_FAILURE);
    }
    return NULL;
}
