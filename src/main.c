#include <stdio.h>
#include <curl/curl.h>
#include <data_req.h>
#include <unistd.h>
#include <jansson.h>
#include <parse.h>
#include "filesystem.h"

int validate_api_key(struct string *api_key) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    struct string *json_res = get_user(api_key);
	curl_global_cleanup();

    json_error_t error;
    json_t *root = json_loads(json_res->ptr, 0, &error);
    deinit_string(json_res);
    if (!json_is_object(root)) {
        fprintf(stderr, "error: root is not an object\n");
        json_decref(root);
        return 0;
    }
    json_t *invalid = json_object_get(root, "error");
    if (invalid) {
        fprintf(stderr, "error: api key is not pointing at a valid user\nPlease check your api key\n");
        json_decref(root);
        json_decref(invalid);
        return 0;
    }
    json_decref(root);
    json_decref(invalid);
    return 1;
}

void check_data_folder() {
    struct string *data_path = string_from_char_arr("data");
    check_or_create_dir(data_path);
    deinit_string(data_path);
}

void get_data_on(int year, int month, int day) {
    check_data_folder();
    struct string *api_key = get_api_key();
    if (validate_api_key(api_key)) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        struct string *date = construct_date_string(year, month, day);
        struct string *summaries = get_summaries(date, api_key);
        curl_global_cleanup();   
        deinit_string(api_key);
        json_error_t error;
        json_t *root = json_loads(summaries->ptr, 0, &error);
        json_t *parsed = parse_single_day(root);
        printf("%s\n", json_dumps(parsed, JSON_ENCODE_ANY));
        struct string *path = string_from_char_arr("data/");
        size_t new_len = path->len + date->len;
        path->len = new_len;
        path->ptr = realloc(path->ptr, new_len);
        sprintf(path->ptr, "%s%s", path->ptr, date->ptr);
        json_dump_file(parsed, path->ptr, JSON_ENCODE_ANY);
        json_decref(root);
        json_decref(parsed);
        deinit_string(date);
        deinit_string(path);
    } else {
        fprintf(stderr, "error: invalid api key\nCheck your api key file\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **args) { 
    if (argc == 1) {
        fprintf(stderr, "error: no command issued, exiting program\n");
        return 1;
    } else { 
        if (strcmp(args[1], "get") == 0) {
            if (argc == 5) {
                get_data_on(atoi(args[2]), atoi(args[3]), atoi(args[4]));
            } else {
                fprintf(stderr, "error: insufficient parameters for get data\n");
                return 1;
            }
        } else {
            fprintf(stderr, "error: invalid command issued %s\n", args[0]);
            return 1;
        }
    } 
	return 0;
}
