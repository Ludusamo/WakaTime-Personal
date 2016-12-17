#ifndef DATA_REQ_H
#define DATA_REQ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "str.h"

#define USER_URL "https://wakatime.com/api/v1/users/current"
#define SUMMARIES_URL "https://wakatime.com/api/v1/users/current/summaries"

struct string* construct_user_url(struct string *api_key);
struct string* get_user(struct string *api_key);
struct string* construct_date_string(int year, int month, int day);
struct string* construct_summaries_url(struct string *date_string, struct string *api_key);
struct string* get_summaries(struct string *date_string, struct string *api_key);

struct string* request_data(struct string *url);
size_t aggregate_data_to_string(char *ptr, size_t size, size_t nmemb, struct string *userdata);

#endif // DATA_REQ_H
