#ifndef CONFIG_H
#define CONFIG_H

#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define CONFIG_PATH "bin/conig.json"

json_t *get_config_json();
void config_update_string_value(struct string *key, struct string *value);
struct string *config_get_string_value(struct string *key);

void set_api_key(char *api_key);
void set_data_path(char *data_path);

#endif // CONFIG_H
