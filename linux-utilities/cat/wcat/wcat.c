#include <stdio.h>
#include <stdlib.h>

void readFile(char *f)
{
    FILE *fp = fopen(f, "r");

    if (fp == NULL)
    {
        printf("wcat: cannot open file\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, fp)) != -1)
    {
        printf("%s", line);
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    // argv[0] -> wcat
    for (int i = 1; i < argc; i++)
    {
        readFile(argv[i]);
    }
    return 0;
}