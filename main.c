#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "correction.h"

char string[100] = {};
char s[15][50] = {};

void clear() // clear strings
{
    for (int i = 0; i < 100; i++)
    {
        string[i] = '\0';
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            s[i][j] = '\0';
        }
    }
}

void input() // input function
{
    scanf("%[^\n]%*c", string);
    int len = strlen(string);
    int counter1 = 0;
    int counter2 = 0;
    int counterq = 0;
    int flag = 0;
    s[0][0] = string[0];
    counter2++;
    for (int i = 1; i < len; i++)
    {
        if (string[i] == 32 && counterq % 2 == 0)
        {
            counter1++;
            counter2 = 0;
        }
        else if (string[i] == '"' && string[i - 1] != 92)
        {
            counterq++;
            s[counter1][counter2] = string[i];
            counter2++;
        }
        else
        {
            s[counter1][counter2] = string[i];
            counter2++;
        }
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

void insertstr(char dir[], char string[], int line, int start) // insertstr
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

void removestr(char dir[], int line, int start, int size, char mode)
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
        if (mode == 'b') // mode -b
        {
            int pcounter = 0;
            while (pcounter != size + 1)
            {
                str1[istr1] = '\0';
                istr1--;
                pcounter++;
            }
        }
        else if (mode == 'f') // mode -f
        {
            for (int i = 0; i < istr2 - size; i++)
            {
                str2[i] = str2[i + size];
            }
            str2[istr2 - size] = '\0';
        }
        file = fopen(buff, "w");
        fprintf(file, "%s%s", str1, str2);
        fclose(file);
    }
}

void copystr(char dir[], int line, int start, int size, char mode)
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

        char copy[100] = {};
        file = fopen(".temp.txt", "w");
        if (mode == 'b')
        {
            int counter = 0;
            for (int i = istr1 - size; i < istr1; i++)
            {
                copy[counter] = str1[i];
                counter++;
            }
        }
        if (mode == 'f')
        {
            for (int i = 0; i < size; i++)
            {
                copy[i] = str2[i];
            }
        }
        fprintf(file, "%s", copy);
        fclose(file);
    }
}

int grep(char pat[], char directory[], int mode)
{
    int counter = 0;
    int ans = 0;
    FILE *file;
    char line[100] = {};
    file = fopen(directory + 1, "r");
    fgets(line, 100, file);
    while (line[0] != '\0') // line
    {
        ans = findinline(line, pat);
        if (ans != 0)
        {
            if (mode == 1)
            {
                printf("%s: %s", directory + 1, line);
            }
            counter++;
        }
        ans = 0;
        for (int i = 0; i < 100; i++)
        {
            line[i] = '\0';
        }
        fgets(line, 100, file);
    }
    if (mode == 1)
    {
        printf("\n");
    }

    if (counter != 0 && mode == 2)
    {
        printf("%s\n", directory + 1);
    }
    return counter;
}

void cat(char *dir) // cat
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
    printf("\n");
}

int main()
{
    while (strcmp(s[0], "exit") != 0)
    {
        clear();
        input();

        if (strcmp(s[0], "createfile") == 0) // createfile
        {
            if (strcmp(s[1], "-file") != 0)
            {
                printf("Invalid input.\n");
            }
            else
            {
                createfile(corstr(s[2]));
            }
        }

        else if (strcmp(s[0], "insertstr") == 0) // insertstr
        {

            if (strcmp(s[1], "-file") != 0 || strcmp(s[3], "-str") != 0 || strcmp(s[5], "-pos") != 0)
            {
                printf("Invalid input.\n");
            }
            else
            {

                insertstr(corstr(s[2]), corstr(s[4]), pos(s[6], 1), pos(s[6], 2)); // need to make pos function
            }
        }

        else if (strcmp(s[0], "removestr") == 0) // remove str
        {
            if (strcmp(s[1], "-file") != 0 || strcmp(s[3], "-pos") != 0 || strcmp(s[5], "-size") != 0)
            {
                printf("Invalid input.\n");
            }
            else if (strcmp(s[7], "-b") == 0 || strcmp(s[7], "-f") == 0)
            {
                removestr(corstr(s[2]), pos(s[4], 1), pos(s[4], 2), change(s[6]), s[7][1]);
            }
            else
            {
                printf("Invalid input.\n");
            }
        }

        else if (strcmp(s[0], "cat") == 0) // cat
        {

            if (strcmp(s[1], "-file") != 0)
            {
                printf("Invalid input.\n");
            }
            else
            {
                cat(corstr(s[2]));
            }
        }

        else if (strcmp(s[0], "copystr") == 0) // copystr
        {
            if (strcmp(s[1], "-file") != 0 || strcmp(s[3], "-pos") != 0 || strcmp(s[5], "-size") != 0)
            {
                printf("Invalid input.\n");
            }
            else if (strcmp(s[7], "-b") == 0 || strcmp(s[7], "-f") == 0)
            {
                copystr(corstr(s[2]), pos(s[4], 1), pos(s[4], 2), change(s[6]), s[7][1]);
            }
            else
            {
                printf("Invalid input.\n");
            }
        }

        else if (strcmp(s[0], "cutstr") == 0) // cutstr
        {
            if (strcmp(s[1], "-file") != 0 || strcmp(s[3], "-pos") != 0 || strcmp(s[5], "-size") != 0)
            {
                printf("Invalid input.\n");
            }
            else if (strcmp(s[7], "-b") == 0 || strcmp(s[7], "-f") == 0)
            {
                copystr(corstr(s[2]), pos(s[4], 1), pos(s[4], 2), change(s[6]), s[7][1]);
                removestr(corstr(s[2]), pos(s[4], 1), pos(s[4], 2), change(s[6]), s[7][1]);
            }
            else
            {
                printf("Invalid input.\n");
            }
        }

        else if (strcmp(s[0], "pastestr") == 0) // pastestr
        {
            if (strcmp(s[1], "-file") != 0 || strcmp(s[3], "-pos") != 0)
            {
                printf("Invalid input.\n");
            }
            else
            {
                FILE *file;
                file = fopen(".temp.txt", "r");
                char paste[100];
                char c;
                int counter = 0;
                c = fgetc(file);
                while (c != EOF)
                {
                    paste[counter] = c;
                    counter++;
                    c = fgetc(file);
                }
                fclose(file);
                insertstr(corstr(s[2]), paste, pos(s[4], 1), pos(s[4], 2)); // need to make pos function
            }
        }

        else if (strcmp(s[0], "grep") == 0)
        {

            int mode;
            int ans;
            int plus;
            int counter = 0;
            if (strcmp(s[1], "-l") == 0) // mode 2
            {
                mode = 2;
                plus = 1;
            }
            else if (strcmp(s[1], "-c") == 0) // mode 3
            {
                mode = 3;
                plus = 1;
            }
            else // mode 1
            {
                mode = 1;
                plus = 0;
            }
            if (strcmp(s[1 + plus], "-str") != 0 || strcmp(s[3 + plus], "-files") != 0)
            {
                printf("Invalid input.\n");
            }
            else
            {
                while (s[4 + plus + counter][0] != '\0')
                {
                    ans += grep(s[2 + plus], s[4 + plus + counter], mode);
                    counter++;
                }
                if (mode == 3)
                {
                    printf("%d\n", ans);
                }
            }
        }

        else if (strcmp(s[0], "exit") != 0) // invalid input // when enter in inputed bug happens
        {
            printf("Invalid input!\n");
        }
    }
}