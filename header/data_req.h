#ifndef DATA_REQ_H
#define DATA_REQ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "str.h"

#define USER_URL "https://wakatime.com/api/v1/users/current?api_key="

struct string* get_user(char *api_key);
size_t aggregate_data_to_string(char *ptr, size_t size, size_t nmemb, struct string *userdata);

#endif // DATA_REQ_H
