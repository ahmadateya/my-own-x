#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int CMD_TOKENS = 3;
const int MAX_KEY_LEN = 250;
const int MAX_VALUE_LEN = 1000;

void bad_command(char *message) {
    printf("bad command\n");
    if (*message == '\0') {
        printf("error: %s\n", message);
    }
    printf("command format: operation(p, g, a, c, or d),key,value \n");
    exit(1);
}

void get_cmd_tokens(char full_command[], char** cmd_tokens) {
    char *token;
    char *delim = ",";

    // Split the full command into tokens
    int i = 0;
    while ((token = strsep(&full_command, delim)) != NULL) {
        // Allocate memory for each individual string based on its content
        cmd_tokens[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(cmd_tokens[i], token);
        i++;
    }
    // check on the number of tokens
    if (i != CMD_TOKENS) {
        bad_command("wrong number of tokens");
    }
}

void validate_command(char *operation, char *key, char *value) {
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

void put(char *key, char *value) {
    printf("put operation\n");
    printf("key: %s\n", key);
    printf("value: %s\n", value);
}

void get(char *key, char *value) {
    printf("get operation\n");
    printf("key: %s\n", key);
    printf("value: %s\n", value);
}

void clear(char *key, char *value) {
    printf("clear operation\n");
    printf("key: %s\n", key);
    printf("value: %s\n", value);
}

void delete(char *key, char *value) {
    printf("delete operation\n");
    printf("key: %s\n", key);
    printf("value: %s\n", value);
}

void append(char *key, char *value) {
    printf("delete operation\n");
    printf("key: %s\n", key);
    printf("value: %s\n", value);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        // array of strings (pointers of pointers) to store the command tokens
        char** cmd_tokens = malloc(sizeof(char*) * CMD_TOKENS);
        get_cmd_tokens(argv[i], cmd_tokens);
        // validate command tokens
        validate_command(cmd_tokens[0], cmd_tokens[1], cmd_tokens[2]);
        char *operation = cmd_tokens[0]; // p, g, a, c, d
        switch (*operation) {
            case 'p': // put a key-value pair
                put(cmd_tokens[1], cmd_tokens[2]);
                break;
            case 'g': // get the value
                get(cmd_tokens[1], cmd_tokens[2]);
                break;
            case 'a': // append to the value
                append(cmd_tokens[1], cmd_tokens[2]);
                break;
            case 'c': // clear the DB
                clear(cmd_tokens[1], cmd_tokens[2]);
                break;
            case 'd': // delete a key
                delete(cmd_tokens[1], cmd_tokens[2]);
                break;
            default:
                bad_command("unknown operation");
        }
        free(cmd_tokens);
    }
    return 0;
}