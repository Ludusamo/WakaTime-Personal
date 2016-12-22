#ifndef PARSE_H
#define PARSE_H

#include <jansson.h>
#include <str.h>

json_t *parse_single_day(json_t *root);
json_t *extract_name_time(json_t *arr);

#endif // PARSE_H
