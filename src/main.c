#include <stdio.h>
#include <curl/curl.h>
#include <data_req.h>

int main() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	printf("%s\n", get_user("")->ptr);
	curl_global_cleanup();
	return 0;
}
