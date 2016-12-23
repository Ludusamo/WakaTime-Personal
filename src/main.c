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

int main() { 
    check_or_create_dir(string_from_char_arr("data/"));

	FILE *api_key_file = fopen("bin/api_key", "r");
	if (api_key_file) {
		struct string *api_key = malloc(sizeof(struct string));
		api_key->ptr = malloc(37);
		api_key->len = 37;
		fscanf(api_key_file, "%s", api_key->ptr);
		printf("%s\n", api_key->ptr);
		
		curl_global_init(CURL_GLOBAL_DEFAULT);
		struct string *summaries = get_summaries(construct_date_string(2016, 12, 14), api_key);
        json_error_t error;
        json_t *root = json_loads(summaries->ptr, 0, &error);
        json_t *parsed = parse_single_day(root);
        printf("%s\n", json_dumps(parsed, JSON_ENCODE_ANY));
		curl_global_cleanup(); 

        if (validate_api_key(api_key)) {
            printf("Valid api key\n");
        } else {
            return 1;
        }
	} else {
		printf("No api file\n");	
		return 1;
	}
	return 0;
}
