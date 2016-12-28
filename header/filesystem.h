#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "str.h"
#include "config.h"
#include <stdio.h>

void check_or_create_dir(struct string *path);
struct string *get_api_key();
struct string *construct_data_path();

#endif // FILESYSTEM_H
