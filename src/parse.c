#include <parse.h>

json_t *parse_single_day(json_t *root) {
    if (!json_is_object(root)) {
        fprintf(stderr, "error: invalid root object\n");
        json_decref(root);
        exit(EXIT_FAILURE);
    }
    json_t *data = json_object_get(root, "data");
    if (!json_is_array(data)) {
        fprintf(stderr, "error: data is not an array\n");
        json_decref(root);
        json_decref(data);
        exit(EXIT_FAILURE);
    }
    json_t *day = json_array_get(data, 0);
    if (!json_is_object(day)) {
        fprintf(stderr, "error: day is not an object\n");
        json_decref(root);
        json_decref(data);
        json_decref(day);
        exit(EXIT_FAILURE);
    }
    
    json_t *editors = json_object_get(day, "editors");
    json_t *entities = json_object_get(day, "entities");
    json_t *languages = json_object_get(day, "languages");
    json_t *operating_systems = json_object_get(day, "operating_systems");
    json_t *projects = json_object_get(day, "projects");

    json_t *json_root = json_object();
    json_object_set(json_root, "editors", extract_name_time(editors));
    json_object_set(json_root, "entities", extract_name_time(entities));
    json_object_set(json_root, "languages", extract_name_time(languages));
    json_object_set(json_root, "operating_systems", extract_name_time(operating_systems));
    json_object_set(json_root, "projects", extract_name_time(projects));

    json_decref(root);
    json_decref(data);
    json_decref(day);
    json_decref(editors);
    json_decref(entities);
    json_decref(languages);
    json_decref(operating_systems);
    json_decref(projects);

    return json_root;
}

json_t *extract_name_time(json_t *arr) {
    size_t index;
    json_t *val;
    json_t *n_arr = json_array();
    json_array_foreach(arr, index, val) {
        json_t *e = json_object();
        json_object_set(e, "name", json_object_get(val, "name"));
        json_object_set(e, "total_seconds", json_object_get(val, "total_seconds"));
        json_array_append(n_arr, e);
    }
    return n_arr;
}
