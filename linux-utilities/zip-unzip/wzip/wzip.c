#include <stdio.h>
#include <stdlib.h>

void zip(FILE *fp)
{
    char *buffer;
    size_t len = 0;
    size_t read;

    char ch;
    int count = 0, start = 1;

    while ((read = getline(&buffer, &len, fp)) != -1)
    {
        for (int i = 0; i < read; i++)
        {
            if (start == 1) // first time ever
            {
                start = 0;
                ch = buffer[i];
                count = 1;
            }
            else if (ch == buffer[i]) // repeated char
            {
                count++;
            }
            else
            {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&ch, sizeof(char), 1, stdout);
                ch = buffer[i];
                count = 1;
            }
        }
    }
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&ch, sizeof(char), 1, stdout);

    fclose(fp);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *all = fopen("./tmp.z", "w+");

    // add all files content into one file
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            fputc(ch, all);
        }
        fclose(fp);
    }
    // sets the file position to the beginning of the file of the given stream
    rewind(all);
    zip(all);
    return 0;
}