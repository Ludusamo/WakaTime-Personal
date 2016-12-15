#include <stdio.h>
#include <curl/curl.h>
#include <data_req.h>

int main() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	printf("%s\n", get_user("ad5017c4-ace5-47d9-93f1-5a830be9646d")->ptr);
	curl_global_cleanup();
	return 0;
}
