#include "config.h"

json_t *get_config_json() {
    json_t *json;
    json_error_t error;
    json = json_load_file(CONFIG_PATH, 0, &error);
    if(!json) {
        return json_object();
    }
    return json;
}

void config_update_string_value(struct string *key, struct string *value) {
    json_t *config = get_config_json();
    json_t *val = json_string(value->ptr);
    json_object_set(config, key->ptr, val);
    json_dump_file(config, CONFIG_PATH, JSON_ENCODE_ANY);
    json_decref(config);
    json_decref(val);
}

struct string *config_get_string_value(struct string *key) {
    json_t *config = get_config_json();
    json_t *val = json_object_get(config, key->ptr);
    struct string *string_val = string_from_char_arr((char *)json_string_value(val));
    json_decref(config);
    json_decref(val);
    return string_val;
}

void set_api_key(char *api_key) {
    struct string *key = string_from_char_arr("api_key");
    struct string *val = string_from_char_arr(api_key);
    config_update_string_value(key, val);
    deinit_string(key);
    deinit_string(val);
}

void set_data_path(char *data_path) {
	struct string *key = string_from_char_arr("data_path");
	struct string *val = string_from_char_arr(data_path);
	config_update_string_value(key, val);
	deinit_string(key);
	deinit_string(val);
}

