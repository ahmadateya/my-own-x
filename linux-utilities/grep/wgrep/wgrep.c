#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024
char buffer[MAX_BUFFER_SIZE];

void grep(FILE *file, const char *pattern)
{
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (strstr(buffer, pattern) != NULL)
        {
            printf("%s", buffer);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];
    if (argc == 2)
    {
        grep(stdin, pattern);
        return 0;
    }
    else
    {
        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        grep(file, pattern);
        fclose(file);
        return 0;
    }
}
