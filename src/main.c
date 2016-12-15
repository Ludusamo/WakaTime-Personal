#include <stdio.h>
#include <curl/curl.h>
#include <data_req.h>

int main() {
	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://wakatime.com/api/v1/users/current/summaries?start=2016-12-08&end=2016-12-14&api_key=");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, aggregate_data_to_string);
		char *data = malloc(sizeof(char));
		data[0] = '\0';
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		data = (char*) realloc(data, strlen(data) + 1);
		data[strlen(data) - 1] = '\0';
		printf("%s\n", data);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}
