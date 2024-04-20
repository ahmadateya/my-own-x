#ifndef HASHMAP_H
#define HASHMAP_H

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

// Function prototypes (declarations)
HashMap* create_hashmap(int capacity);
void insert(HashMap* map, const char* key, char* value);
//char* get(HashMap* map, const char* key);
//void remove(HashMap* map, const char* key); // Optional function for removing entries
//void destroy_hashmap(HashMap* map); // Optional function for freeing memory
void print_hashmap(HashMap* map); // Optional function for debugging
#endif
