#include <data_req.h>

struct string* construct_user_url(char *api_key) {
	struct string *url = malloc(sizeof(struct string));
	init_string(url);
	size_t new_len = strlen(USER_URL) + strlen("?api_key=") + strlen(api_key) + 1;
	url->ptr = realloc(url->ptr, new_len);
	sprintf(url->ptr, "%s?api_key=%s", USER_URL, api_key);
	url->len = new_len;
	return url;
}

struct string* get_user(char *api_key) {
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();

	struct string *s = malloc(sizeof(struct string));
	init_string(s);
	if (curl) {
		struct string *url = construct_user_url(api_key);
		printf("%s\n", url->ptr);
		curl_easy_setopt(curl, CURLOPT_URL, url->ptr);
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

struct string* construct_date_string(int year, int month, int day) {
	if (year / 1000 > 9 || month / 13 != 0 || day / 100 != 0) {
		fprintf(stderr, "Invalid year, date, and month parameters.");
		exit(EXIT_FAILURE);
	}
	struct string *date = malloc(sizeof(struct string));
	init_string(date);
	date->ptr = realloc(date->ptr, 10);
	date->len = 10;
	sprintf(date->ptr, "%04d-%02d-%02d", year, month, day);
	return date;
}

struct string* construct_summaries_url(char *date_string, char *api_key) {
	struct string *url = malloc(sizeof(struct string));
	init_string(url);
	size_t new_len = strlen(SUMMARIES_URL) + strlen("?start=&end=&api_key=") + strlen(date_string) + strlen(api_key);
	url->ptr = realloc(url->ptr, new_len);
	sprintf(url->ptr, "%s?start=%s&end=%s&api_key=%s", SUMMARIES_URL, date_string, date_string, api_key);
	url->len = new_len;
	return url;
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
