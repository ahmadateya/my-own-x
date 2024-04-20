#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct KeyValuePair {
    char* key;
    char* value;
} KeyValuePair;

typedef struct HashMap {
    int capacity;
    KeyValuePair** pairs;
} HashMap;

HashMap* create_hashmap(int capacity);
void insert(HashMap* map, const char* key, char* value);
char* get_value(HashMap* map, const char* key);
void remove_pair(HashMap* map, const char* key);
void remove_all_pairs(HashMap* map);
void destroy_hashmap(HashMap* map);
void print_hashmap(HashMap* map);
#endif
