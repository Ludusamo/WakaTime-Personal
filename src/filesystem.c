#include "filesystem.h"

void check_or_create_dir(struct string *path) {
    struct stat st = {0};

    printf("%s\n", path->ptr);
    if (stat(path->ptr, &st) == -1) {
        mkdir(path->ptr, 0700);
    }
}
