#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "str.h"

void check_or_create_dir(struct string *path);

#endif // FILESYSTEM_H
