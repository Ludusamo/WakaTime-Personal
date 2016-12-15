#include <stdio.h>
#include <curl/curl.h>
#include <data_req.h>
#include <unistd.h>

int main() {
	FILE *api_key_file = fopen("bin/api_key", "r");
	if (api_key_file) {
		char api_key[37];
		fscanf(api_key_file, "%s", api_key);
		api_key[36] = '\0';
		printf("%s\n", api_key);
		
		curl_global_init(CURL_GLOBAL_DEFAULT);
		printf("%s\n", get_user(api_key)->ptr);
		curl_global_cleanup();
	} else {
		printf("No api file\n");	
		return 1;
	}
	return 0;
}
