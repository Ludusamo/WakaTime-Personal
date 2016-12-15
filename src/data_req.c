#include <data_req.h>

size_t aggregate_data_to_string(char *ptr, size_t size, size_t nmemb, void *userdata) {
	userdata = (char*) realloc((char*)userdata, strlen((char*)userdata) + strlen(ptr));
	strcat((char*)userdata, ptr);
	return size * nmemb;
}
