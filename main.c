#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "correction.h"

char string[100] = {};
void clear() // clear string
{
    for (int i = 0; i < 100; i++)
    {
        string[i] = '\0';
    }
}

void createfile(char *string) // createfile
{
    char buff[100] = {};
    int len = strlen(string);

    for (int i = 1; i < len; i++) // creating directory
    {
        buff[i - 1] = string[i];
        if (string[i + 1] == '/')
        {
            mkdir(buff, 0777);
        }
    }

    FILE *file; // check file
    if (fopen(buff, "r") == 0)
    {
        file = fopen(buff, "w");
    }
    else
    {
        printf("File already exists.\n");
    }
    fclose(file);
}

void insert(char directory[], char string[], int line, int start)
{
    char *add = "/Users/Radin/School/Programming/project-radinshahdaei";
    int addlen = strlen(add);
    int len = strlen(directory);
    char address[200];
    for (int i = 0; i < addlen; i++) // creating address for file
    {
        address[i] = add[i];
    }
    for (int i = 0; i < len; i++)
    {
        address[addlen + i] = directory[i];
    }

    if (fopen(address, "r") == 0)
    {
        printf("File does not exist.\n");
    }
    else
    {
        FILE *file;
        file = fopen(address, "w");
        int counter1 = 1;
        int counter2 = 0;
        char c;
        while (counter1 != line && counter2 != start)
        {
            c = fgetc(file);
            counter2++;
            if (c == '\n')
            {
                counter1++;
                counter2 = 0;
            }
        }
        fputs(string, file);
    }
}

int main()
{
    while (strcmp(string, "exit") != 0)
    {
        clear();
        scanf("%s", string);

        if (strcmp(string, "createfile") == 0) // createfile
        {
            clear();
            scanf("%s", string);

            if (strcmp(string, "-f") == 0)
            {
                getchar();

                clear();
                scanf("%[^\n]", string);
                createfile(corstr(string));
            }
            else
            {
                printf("Invalid input.\n");
            }
        }

        else if (strcmp(string, "exit") != 0) // invalid input
        {
            scanf("%[^\n]", string);
            printf("Invalid input.\n");
        }
    }
}