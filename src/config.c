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
