#include "filesystem.h"

void check_or_create_dir(struct string *path) {
    struct stat st = {0};

    if (stat(path->ptr, &st) == -1) {
        mkdir(path->ptr, 0700);
    }
}

struct string *get_api_key() {
    struct string *key = string_from_char_arr("api_key");
    struct string *api_key = config_get_string_value(key);
    deinit_string(key);
    return api_key;
}
