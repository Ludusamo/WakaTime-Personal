#include <stdio.h>
#include <curl/curl.h>
#include <data_req.h>
#include <unistd.h>

int main() {
	printf("%s\n", construct_date_string(2016, 5, 22)->ptr);
	FILE *api_key_file = fopen("bin/api_key", "r");
	if (api_key_file) {
		struct string *api_key = malloc(sizeof(struct string));
		api_key->ptr = malloc(37);
		api_key->len = 37;
		fscanf(api_key_file, "%s", api_key->ptr);
		printf("%s\n", construct_summaries_url(construct_date_string(2016,5,22), api_key)->ptr);
		printf("%s\n", api_key->ptr);
		
		curl_global_init(CURL_GLOBAL_DEFAULT);
		printf("%s\n", get_user(api_key)->ptr);
		curl_global_cleanup();
	} else {
		printf("No api file\n");	
		return 1;
	}
	return 0;
}
