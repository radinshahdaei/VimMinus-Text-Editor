#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "correction.h"

char string[100] = {};
char add[100] = {};
int a;
int b;
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

void insertstr(char dir[], char string[], int line, int start)
{
    int len = strlen(dir);
    char buff[len - 1];

    for (int i = 0; i < len - 1; i++)
    {
        buff[i] = dir[i + 1];
    }

    if (fopen(buff, "r") == 0) // check file
    {
        printf("File does not exist.\n");
    }

    else
    {
        FILE *file;
        file = fopen(buff, "r");
        char str1[1000] = {'\0'};
        char str2[1000] = {'\0'};
        int counter1 = 1;
        int counter2 = 0;
        int istr1 = 0;
        int istr2 = 0;
        char c = '\0';

        while (counter1 != line || counter2 != start) // going to location
        {
            c = fgetc(file);
            str1[istr1] = c; // string 1
            istr1++;
            counter2++;
            if (c == '\n')
            {
                counter1++;
                counter2 = 0;
            }
        }

        c = fgetc(file); // string 2
        while (c != EOF)
        {
            str2[istr2] = c;
            istr2++;
            c = fgetc(file);
        }

        fclose(file);
        file = fopen(buff, "w");
        fprintf(file, "%s%s%s", str1, string, str2);
        fclose(file);
    }
}

void cat(char *dir)
{
    int len = strlen(dir);
    char buff[len - 1];

    for (int i = 0; i < len - 1; i++)
    {
        buff[i] = dir[i + 1];
    }
    if (fopen(buff, "r") == 0) // check file
    {
        printf("File does not exist.\n");
    }

    else
    {
        char c;
        FILE *file;
        file = fopen(buff, "r");
        c = fgetc(file);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(file);
        }
        fclose(file);
    }
}

int main()
{
    // char *str = malloc(100 * sizeof(char));
    // scanf("%s ", string);
    // str = get_string(str);
    // printf("%s", corstr(str));

    while (strcmp(string, "exit") != 0)
    {
        clear();
        scanf("%s", string);

        if (strcmp(string, "createfile") == 0) // createfile
        {
            clear();
            if (!(scanf(" -file %s", string)))
            {
                printf("Invalid input.\n");
            }
            else
            {
                createfile(corstr(string));
            }
        }

        else if (strcmp(string, "insertstr") == 0) // insertstr
        {
            clear();
            if (!(scanf(" -file %s -str %s -pos %d:%d", add, string, &a, &b)))
            {
                printf("Invalid input.\n");
            }
            else
            {
                insertstr(corstr(add), corstr(string), a, b);
            }
        }

        else if (strcmp(string, "cat") == 0) // cat
        {
            clear();
            if (!(scanf(" -file %s", string)))
            {
                printf("Invalid input.\n");
            }
            else
            {
                cat(corstr(string));
            }
        }
        else if (strcmp(string, "exit") != 0) // invalid input
        {
            scanf("%[^\n]", string);
            printf("Invalid input.\n");
        }
    }
}