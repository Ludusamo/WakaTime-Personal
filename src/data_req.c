#include <data_req.h>

struct string* get_user(char *api_key) {
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();

	struct string *s = malloc(sizeof(struct string));
	init_string(s);
	if (curl) {
		char url[strlen(USER_URL) + strlen(api_key) + 1];
		strcpy(url, USER_URL);
		strcat(url, api_key);
		url[strlen(USER_URL) + strlen(api_key)] = '\0';
		printf("%s\n", url);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, aggregate_data_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, s);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		curl_easy_cleanup(curl);
	}
	return s;
}

size_t aggregate_data_to_string(char *ptr, size_t size, size_t nmemb, struct string *s) {
	size_t new_len = s->len + size*nmemb;
	s->ptr = realloc(s->ptr, new_len + 1);
	if (s->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->ptr + s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size * nmemb;
}
