#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValuePair {
    char* key;
    char* value;
} KeyValuePair;

typedef struct HashMap {
    int capacity;
    KeyValuePair** pairs;
} HashMap;


// Hash function (simple string hashing based on character sum)
int hash_function(const char* key, int capacity) {
    int hash = 0;
    while (*key) {
        hash += (int)*key;
        key++;
    }
    return hash % capacity;
}

HashMap* create_hashmap(int capacity) {
    HashMap* map = malloc(sizeof(HashMap));
    map->capacity = capacity;

    // Allocate memory for the array of pairs (pointers to linked lists)
    map->pairs = malloc(sizeof(KeyValuePair*) * capacity);
    for (int i = 0; i < capacity; i++) {
        map->pairs[i] = NULL;
    }
    return map;
}

void trim_newline(char *str) {
    char *pos = strchr(str, '\n');
    if (pos != NULL) {
        *pos = '\0';
    }
}

void insert(HashMap* map, const char* key, char* value) {
    int index = hash_function(key, map->capacity);

    KeyValuePair* new_pair = malloc(sizeof(KeyValuePair));
    new_pair->key = malloc(strlen(key) + 1); // Allocate memory for the key string
    strcpy(new_pair->key, key);
    trim_newline(value);
    new_pair->value = value;

    map->pairs[index] = new_pair;
}

char* get_value(HashMap* map, const char* key) {
    int index = hash_function(key, map->capacity);

    KeyValuePair* current = map->pairs[index];
    if (current == NULL) {
        return NULL;
    }
    return current->value;
}

void remove_pair(HashMap* map, const char* key) {
    int index = hash_function(key, map->capacity);

    KeyValuePair* current = map->pairs[index];
    if (current != NULL) {
        map->pairs[index] = NULL;
    }
}

void remove_all_pairs(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        KeyValuePair *current = map->pairs[i];
        if (current != NULL) {
            map->pairs[i] = NULL;
        }
    }
}


void destroy_hashmap(HashMap* map) {
    free(map);
}


// Print the contents of the hashmap (for debugging)
void print_hashmap(HashMap* map) {
    for (int i = 1; i <= map->capacity; i++) {
        KeyValuePair* current = map->pairs[i];
        if (current != NULL) {
            printf("Pair %2d: ", i);
            printf("%s -> %s\n", current->key, current->value);
        }
    }
}
