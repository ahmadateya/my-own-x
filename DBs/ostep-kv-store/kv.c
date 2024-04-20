#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

const int MAX_CMD_TOKENS = 3;
const int MAX_KEY_LEN = 250;
const int MAX_VALUE_LEN = 1000;
const char *delim = ",";

HashMap* db_map;
const int DB_SIZE = 100;

void bad_command(char* message) {
    printf("bad command\n");
    if (*message == '\0') {
        printf("kv: error: %s\n", message);
    }
    printf("kv: command format: operation(p, g, a, c, or d),key,value \n");
    exit(1);
}

void get_cmd_tokens(char full_command[], char** cmd_tokens) {
    char *token;

    // Split the full command into tokens
    int i = 0;
    while ((token = strsep(&full_command, delim)) != NULL) {
        // Allocate memory for each individual string based on its content
        cmd_tokens[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(cmd_tokens[i], token);
        i++;
    }
}

void validate_command(char* operation, char* key, char* value) {
    if (*operation == 'p' && key == NULL && value == NULL) {
        bad_command("wrong number of tokens");
    }

    if (key == NULL) {
        return;
    }

    if (*key == '\0') {
        bad_command("key is missing");
    }
    if (strlen(key) > MAX_KEY_LEN) {
        bad_command("key is too long");
    }
    if (strlen(value) > MAX_VALUE_LEN) {
        bad_command("value is too long");
    }
}

void put(char* key, char* value) {
    insert(db_map, key, value);
}

void get(char* key) {
    char* value = get_value(db_map, key);
    if (value == NULL) {
        printf("key not found\n");
        return;
    }
    printf("%s\n", value);
}

void clear() {
    remove_all_pairs(db_map);
}

void delete(char* key) {
    char* value = get_value(db_map, key);
    if (value == NULL) {
        printf("key not found\n");
        return;
    } else {
        remove_pair(db_map, key);
        printf("key deleted\n");
    }
}

void all() {
    for (int i = 1; i <= db_map->capacity; i++) {
        KeyValuePair* current = db_map->pairs[i];
        if (current != NULL) {
            printf("%s -> %s\n", current->key, current->value);
        }
    }
}

void load_db() {
    FILE* fptr = fopen("./db.txt", "r");
    if (fptr == NULL) {
        printf("kv: cannot open DB file\n");
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    char *token;

    db_map = create_hashmap(DB_SIZE);
    while (getline(&line, &len, fptr) != -1) {
        char* line_tokens[2];
        for (int i = 0; i < 2; ++i) {
            token = strsep(&line, delim);
            if (token == NULL) {
                printf("kv: cannot load DB\n");
                exit(1);
            }
            // Allocate memory for each individual string based on its content
            line_tokens[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(line_tokens[i], token);
        }
        insert(db_map, line_tokens[0], line_tokens[1]);
    }
    fclose(fptr);
}

void save_db() {
    // open the file for writing with the truncation option
    FILE* fptr = fopen("./db.txt", "w");
    if (fptr == NULL) {
        printf("kv: cannot open DB file\n");
        exit(1);
    }
    for (int i = 0; i < db_map->capacity; i++) {
        KeyValuePair* pair = db_map->pairs[i];
        if (pair != NULL) {
            fprintf(fptr, "%s,%s\n", pair->key, pair->value);
        }
    }
    destroy_hashmap(db_map);
    fclose(fptr);
}

int main(int argc, char *argv[]) {
    // load DB file into memory (hash table)
    load_db();

    // iterate over the commands
    for (int i = 1; i < argc; i++) {
        char** cmd_tokens = malloc(sizeof(char*) * MAX_CMD_TOKENS);
        get_cmd_tokens(argv[i], cmd_tokens);
        // validate command tokens
        validate_command(cmd_tokens[0], cmd_tokens[1], cmd_tokens[2]);
        char *operation = cmd_tokens[0]; // p, g, a, c, d
        switch (*operation) {
            case 'p': // put a key-value pair
                put(cmd_tokens[1], cmd_tokens[2]);
                break;
            case 'g': // get the value
                get(cmd_tokens[1]);
                break;
            case 'd': // delete a key
                delete(cmd_tokens[1]);
                break;
            case 'a': // output all key-value pairs
                all();
                break;
            case 'c': // clear the DB
                clear();
                break;
            default:
                bad_command("unknown operation");
        }
        free(cmd_tokens);
    }
    // save the DB back to the file
    save_db();
    return 0;
}