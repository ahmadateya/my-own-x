#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValuePair {
    char* key;
    char* value;
//    struct KeyValuePair* next;
} KeyValuePair;

typedef struct HashMap {
    int capacity;
    KeyValuePair** pairs; // Array of pointers to linked lists of key-value pairs
//    int (*hash_function)(const char* key); // Pointer to the hash function
} HashMap;


// Hash function (simple string hashing based on character sum)
int hash_function(const char* key, int capacity) {
    int hash = 0;
    while (*key) {
        hash += (int)*key;
        key++;
    }
    return hash % capacity; // Ensure hash value falls within bucket range
}

HashMap* create_hashmap(int capacity) {
    HashMap* map = malloc(sizeof(HashMap));
    map->capacity = capacity;

    // Allocate memory for the array of pairs (pointers to linked lists)
    map->pairs = malloc(sizeof(KeyValuePair*) * capacity);
    for (int i = 0; i < capacity; i++) {
        map->pairs[i] = NULL; // Initialize all pairs to NULL
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
//    new_pair->next = NULL;

    // Handle collisions (add to the beginning of the chain)
//    if (map->pairs[index] != NULL) {
//        new_pair->next = map->pairs[index];
//    }
    map->pairs[index] = new_pair;
}

// Get the value associated with a key
//char* get(HashMap* map, const char* key) {
//    // Calculate the hash index
//    int index = hash_function(key);
//
//    // Traverse the linked list at the bucket
//    KeyValuePair* current = map->pairs[index];
//    while (current != NULL) {
//        if (strcmp(current->key, key) == 0) {
//            return current->value; // Key found, return the value
//        }
//        current = current->next;
//    }
//
//    // Key not found
//    return NULL;
//}

// Print the contents of the hashmap (for debugging)
void print_hashmap(HashMap* map) {
    for (int i = 1; i <= map->capacity; i++) {
        KeyValuePair* current = map->pairs[i];
        if (current != NULL) {
            printf("Pair %2d: ", i);
            printf("%s -> %s", current->key, current->value);
            printf("\n");
        }
//        while (current != NULL) {
//            printf("(%s, %p) -> ", current->key, current->value);
//            current = current->next;
//        }
//        printf("NULL\n");
    }
}