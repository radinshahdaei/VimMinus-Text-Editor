#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "correction.h"
#include <sys/types.h>
#include <dirent.h>

char string[200] = {};
char s[20][50] = {};
char ans[200] = {}; // double check for funtionality

int f = 0;
int arman = 0;

void clear() // clear strings
{
    for (int i = 0; i < 200; i++)
    {
        string[i] = '\0';
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            s[i][j] = '\0';
        }
    }
}

void clearans()
{
    for (int i = 0; i < 200; i++)
    {
        ans[i] = '\0';
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

void createcopy(char *dir)
{
    FILE *file;
    FILE *copy;
    file = fopen(dir + 1, "r");

    int counter = 0;
    int len = strlen(dir);
    while (dir[len - 1 - counter] != '/')
    {
        counter++;
    }
    char buff[50] = {};
    strncat(buff, dir, len - counter);
    strcat(buff, ".");
    strcat(buff, dir + len - counter);

    copy = fopen(buff + 1, "w");
    char c;
    c = fgetc(file);
    while (c != EOF)
    {
        fprintf(copy, "%c", c);
        c = fgetc(file);
    }
    fclose(file);
    fclose(copy);
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
        clearans();
        strcat(ans, "File already exists.\n");
        // printf("File already exists.\n");
        return;
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
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
    }

    else
    {
        if (f == 0)
            createcopy(dir);
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

    if (fopen(dir + 1, "r") == 0) // check file
    {
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
    }
    else
    {
        if (f == 0)
            createcopy(dir);
        FILE *file;
        file = fopen(dir + 1, "r");
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
        file = fopen(dir + 1, "w");
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
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
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
    int answer = 0;
    FILE *file;
    char line[300] = {};
    if (fopen(directory + 1, "r") == 0) // check file
    {
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
    }
    else
    {
        file = fopen(directory + 1, "r");
        fgets(line, 300, file);
        while (line[0] != '\0') // line
        {
            answer = findinline(line, pat);
            if (answer != 0)
            {
                if (mode == 1)
                {
                    clearans();
                    strcat(ans, directory + 1);
                    strcat(ans, ": ");
                    strcat(ans, line);
                    if (line[strlen(line) - 1] != '\n')
                    {
                        strcat(ans, "\n");
                    }
                    // printf("%s: %s", directory + 1, line);
                }
                counter++;
            }
            answer = 0;
            for (int i = 0; i < 100; i++)
            {
                line[i] = '\0';
            }
            fgets(line, 300, file);
        }

        if (counter != 0 && mode == 2)
        {
            clearans();
            strcat(ans, directory + 1);
            strcat(ans, "\n");
            // printf("%s\n", directory + 1);
        }
    }
    fclose(file);
    return counter;
}

void find(char pat[], char directory[], int mode, int start, int corw)
{
    int counter = 0;
    int counters = 0;
    int flag = 0;
    int wir = 0;

    FILE *file;
    char line[300] = {};
    int found[50] = {};
    int foundbyword[50] = {};
    int space[50] = {};
    for (int i = 0; i < 50; i++)
    {
        found[i] = -1;
        foundbyword[i] = -1;
        space[i] = -1;
    }

    if (fopen(directory + 1, "r") == 0) // check file
    {
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
    }
    else
    {
        int wild = 0;
        file = fopen(directory + 1, "r");
        fgets(line, 300, file);

        int len = strlen(line) - strlen(pat);
        int length = strlen(pat);

        if (pat[0] == '*')
        {
            wild = 1;
        }
        for (int i = 1; i < len - 1; i++) // checking for wildcard
        {
            if (pat[i] == '*' && pat[i - 1] != 92)
            {
                wild = 1;
            }
            if (pat[i] == '*' && pat[i - 1] == 92) // checking for \*
            {
                for (int j = i - 1; j < len; j++)
                {
                    pat[j] = pat[j + 1];
                }
                pat[len - 1] = '\0';
                pat[len - 2] = '\0';
                wir++;
            }
        }

        for (int i = 0; i < 50; i++) // finding pattern
        {
            char string[100] = {};
            strncpy(string, line + i, length - wir);

            if (line[i] == 32) // spaces
            {
                flag = 0;
                space[counters] = i;
                counters++;
            }

            if (wild == 1) // wild mode
            {

                if (match(pat, string) == 1)
                {
                    // printf("\nWILD!\n");
                    flag++;
                    if (flag == 1)
                    {
                        found[counter] = i;
                        counter++; // number of finds
                    }
                }
            }

            else // cattle mode
            {

                if (strcmp(pat, string) == 0)
                {
                    // printf("\nNOT WILD!\n");
                    flag++;
                    found[counter] = i;
                    counter++; // number of finds
                }
            }
        }

        for (int i = 0; found[i] != -1; i++) // creating byword array
        {
            int max = 1;
            for (int j = 0; space[j] != -1; j++)
            {
                if (space[j] < found[i])
                {
                    max = j + 2;
                }
            }
            foundbyword[i] = max;
        }
        clearans();
        if (mode == 0 && corw == 0) // modes --->
        {
            char buff[10] = {};
            sprintf(buff, "%d\n", found[start]);
            strcat(ans, buff);
            // printf("%d\n", found[start]);
        }

        else if (mode == 0 && corw == 1)
        {
            char buff[10] = {};
            sprintf(buff, "%d\n", foundbyword[start]);
            strcat(ans, buff);
            // printf("%d\n", foundbyword[start]);
        }

        else if (mode == 1)
        {
            char buff[10] = {};
            sprintf(buff, "%d\n", counter);
            strcat(ans, buff);
            // printf("%d\n", counter);
        }

        else if (mode == 2 && corw == 0)
        {
            char buff[10] = {};
            sprintf(buff, "%d", found[0]);
            strcat(ans, buff);
            // printf("%d", found[0]);
            for (int i = 1; found[i] != -1; i++)
            {
                char buff[10] = {};
                sprintf(buff, ", %d", found[i]);
                strcat(ans, buff);
                // printf(", %d", found[i]);
            }
            strcat(ans, "\n");
            // printf("\n");
        }

        else if (mode == 2 && corw == 1)
        {
            char buff[10] = {};
            sprintf(buff, "%d", foundbyword[0]);
            strcat(ans, buff);
            // printf("%d", foundbyword[0]);
            for (int i = 1; foundbyword[i] != -1; i++)
            {
                char buff[10] = {};
                sprintf(buff, "%d", foundbyword[i]);
                strcat(ans, buff);
                // printf(", %d", foundbyword[i]);
            }
            strcat(ans, "\n");
            // printf("\n");
        }
    }
}

int replace(char pat[], char directory[], int start, char rep[])
{
    int counter = 0;
    int counters = 0;
    int flag = 0;
    int wir = 0;

    FILE *file;
    char line[300] = {};
    int found[50] = {};
    int size[50] = {};
    int foundbyword[50] = {};
    int space[50] = {};
    for (int i = 0; i < 50; i++)
    {
        found[i] = -1;
        foundbyword[i] = -1;
        space[i] = -1;
        size[i] = -1;
    }

    if (fopen(directory + 1, "r") == 0) // check file
    {
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
        return 0;
    }
    else
    {

        int wild = 0;
        file = fopen(directory + 1, "r");
        fgets(line, 300, file);

        int len = strlen(line) - strlen(pat);
        int length = strlen(pat);

        if (pat[0] == '*')
        {
            wild = 1;
        }

        for (int i = 1; i < len - 1; i++) // checking for wildcard
        {
            if (pat[i] == '*' && pat[i - 1] != 92)
            {
                wild = 1;
            }
            if (pat[i] == '*' && pat[i - 1] == 92) // checking for \*
            {
                for (int j = i - 1; j < len; j++)
                {
                    pat[j] = pat[j + 1];
                }
                pat[len - 1] = '\0';
                pat[len - 2] = '\0';
                wir++;
            }
        }

        for (int i = 0; i < 50; i++) // finding pattern
        {
            char string[100] = {};
            strncpy(string, line + i, length - wir);

            if (line[i] == 32) // spaces
            {
                flag = 0;
                space[counters] = i;
                counters++;
            }

            if (wild == 1) // wild mode
            {

                if (match(pat, string) == 1)
                {
                    flag++;
                    if (flag == 1)
                    {
                        if (pat[0] == '*' && line[i] == 32)
                        {
                            found[counter] = i + 1;
                        }
                        else
                        {
                            found[counter] = i;
                        }

                        counter++; // number of finds
                    }
                }
            }

            else // cattle mode
            {

                if (strcmp(pat, string) == 0)
                {
                    flag++;
                    found[counter] = i;
                    counter++; // number of finds
                }
            }
        }
        if (counter == 0)
        {
            return 0;
        }

        for (int i = 0; found[i] != -1; i++) // creating byword array
        {
            int max = 1;
            for (int j = 0; space[j] != -1; j++)
            {
                if (space[j] < found[i])
                {
                    max = j + 2;
                }
            }
            foundbyword[i] = max;
        }

        if (wild == 1) // creating size array
        {
            int max = 0;
            if (pat[0] == '*') // wildcard with * start
            {
                for (int i = 0; found[i] != -1; i++)
                {
                    for (int j = 0; space[j] != -1; j++)
                    {
                        if (space[j] < found[i])
                        {
                            max = space[j];
                        }
                    }
                    size[i] = found[i] - max + length - 1 - (line[found[i]] == pat[1]);
                }
            }

            if (pat[length - 1] == '*') // wildcard with * end
            {
                int buff = 0;
                max = space[0];
                for (int i = 0; found[i] != -1; i++)
                {
                    for (int j = 0; space[j] != -1; j++)
                    {
                        if (space[j] < found[i])
                        {
                            max = space[j + 1];
                            buff = found[i];
                        }
                    }
                    if (i == counter - 1)
                    {
                        size[i] = strlen(line) - found[i];
                    }
                    else
                    {
                        size[i] = max - buff;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; found[i] != -1; i++)
            {
                size[i] = length;
            }
        }

        removestr(directory, 1, found[start], size[start], 'f');
        insertstr(directory, rep, 1, found[start]);
    }
    return 1;
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
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
    }

    else
    {
        char c;
        FILE *file;
        file = fopen(buff, "r");
        c = fgetc(file);
        clearans();
        int counter = 0;
        while (c != EOF)
        {
            ans[counter] = c;
            counter++;
            // printf("%c", c);
            c = fgetc(file);
        }
        fclose(file);
        strcat(ans, "\n");
        // printf("\n");
    }
}

int dcounter = 0;
int depth;

void tree(char *basePath, const int root)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.')
        {
            for (i = 0; i < root; i++)
            {
                if (i % 2 == 0 || i == 0)
                    strcat(ans, "│");
                else
                    strcat(ans, " ");
            }

            strcat(ans, "├─");
            strcat(ans, dp->d_name);
            strcat(ans, "\n");
            // printf("├─%s\n", dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            if (dcounter < depth)

            {
                dcounter++;

                tree(path, root + 2);
            }
        }
    }

    closedir(dir);
}

void autoindent(char *dir)
{
    if (fopen(dir + 1, "r") == 0) // check file
    {
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
    }

    else
    {
        createcopy(dir);
        FILE *file;
        file = fopen(dir + 1, "r");
        char line[300] = {};
        fgets(line, 300, file);
        char l[50][50] = {};
        int len = strlen(line);
        int counter1 = 0;
        int counter2 = 0;
        int open = 0;
        int close = 0;

        l[0][0] = line[0];
        if (line[0] == '{' || line[0] == '}')
        {
            counter1++;
        }
        else
        {
            counter2++;
        }
        for (int i = 1; i < len; i++) // creating 2d array
        {
            if (line[i] == '{')
            {
                open++;
                counter1++;
                l[counter1][0] = '{';
                counter1++;
                counter2 = 0;
            }
            else if (line[i] == '}')
            {
                close++;
                counter1++;
                l[counter1][0] = '}';
                counter1++;
                counter2 = 0;
            }
            else
            {
                l[counter1][counter2] = line[i];
                counter2++;
            }
        }
        int ocounter = 0;
        int ccounter = close - 1;

        for (int i = 0; i < 50; i++) // removing white space
        {
            if (l[i][0] != '{' && l[i][0] != '}')
            {
                int len = strlen(l[i]);
                int counter1 = 0;
                while (l[i][counter1] == 32)
                {
                    counter1++;
                }
                int counter2 = 0;
                while (l[i][len - counter2 - 1] == 32)
                {
                    counter2++;
                }
                for (int j = 0; j < len - counter1 - counter2; j++)
                {
                    l[i][j] = l[i][counter1 + j];
                }

                l[i][len - counter1 - counter2] = '\0';
            }
        }

        fclose(file);
        file = fopen(dir + 1, "w");

        for (int i = 0; i < 50; i++) // printing all
        {
            if (l[i][0] != '\0' && l[i][0] != 32)
            {

                fprintf(file, "%s", l[i]);
                if (l[i][0] == '{' || l[i][0] == '}' || l[i + 1][0] == '}')
                {

                    fprintf(file, "\n");

                    if (ocounter < open)
                    {
                        for (int j = 0; j <= ocounter; j++)
                        {
                            fprintf(file, "    ");
                        }
                        ocounter++;
                    }
                    else if (ccounter > 0)
                    {
                        for (int j = 0; j < ccounter; j++)
                        {
                            fprintf(file, "    ");
                        }
                        ccounter--;
                    }
                }
                else if (l[i + 1][0] == '{')
                {
                    fprintf(file, " ");
                }
            }
        }
        fclose(file);
    }
}

void compare(char *dir1, char *dir2)
{
    int counter1 = 0, counter2 = 0;
    int flag = 1;
    FILE *file1;
    FILE *file2;
    char line1[300] = {};
    char line2[300] = {};
    char answer[500] = {};
    if (fopen(dir1 + 1, "r") == 0 || fopen(dir2 + 1, "r") == 0) // check file
    {
        clearans();
        strcat(ans, "File does not exist.\n");
        // printf("File does not exist.\n");
    }
    else
    {

        file1 = fopen(dir1 + 1, "r");
        file2 = fopen(dir2 + 1, "r");
        fgets(line1, 300, file1);
        fgets(line2, 300, file2);
        if (line1[0] != '\0')
        {
            counter1++;
        }
        if (line2[0] != '\0')
        {
            counter2++;
        }

        if (line1[strlen(line1) - 1] != '\n')
        {
            strcat(line1, "\n");
        }
        if (line2[strlen(line2) - 1] != '\n')
        {
            strcat(line2, "\n");
        }

        while (line1[0] != '\0' && line2[0] != '\0' && flag == 1)
        {
            if (counter1 > counter2)
            {
                flag = 0;
            }

            if (counter1 < counter2)
            {
                flag = 0;
            }

            else if (strcmp(line1, line2) != 0)
            {
                char buffer[200] = {};
                sprintf(buffer, "============ %d ============\n%s%s", counter1, line1, line2);
                strcat(ans, buffer);
                // printf("============ %d ============\n", counter1);
                // printf("%s%s", line1, line2);
            }
            for (int i = 0; i < 300; i++)
            {
                line1[i] = '\0';
                line2[i] = '\0';
            }
            fgets(line1, 300, file1);
            fgets(line2, 300, file2);
            if (line1[0] != '\0')
            {
                counter1++;
            }
            if (line2[0] != '\0')
            {
                counter2++;
            }

            if (line1[strlen(line1) - 1] != '\n')
            {
                strcat(line1, "\n");
            }
            if (line2[strlen(line2) - 1] != '\n')
            {
                strcat(line2, "\n");
            }
        }

        if (counter1 > counter2)
        {
            int buff = counter1;
            counter1--;
            strcat(answer, line1);
            while (line1[0] != '\0')
            {
                counter1++;
                for (int i = 0; i < 300; i++)
                {
                    line1[i] = '\0';
                }
                fgets(line1, 300, file1);
                strcat(answer, line1);
            }
            char buffer[200] = {};
            sprintf(buffer, "<<<<<<<<<<<< %d - %d <<<<<<<<<<<<\n%s", buff, counter1, answer);
            strcat(ans, buffer);
            // printf("<<<<<<<<<<<< %d - %d <<<<<<<<<<<<\n%s", buff, counter1, ans);
        }

        if (counter2 > counter1)
        {
            int buff = counter2;
            counter2--;
            strcat(answer, line2);
            while (line2[0] != '\0')
            {
                counter2++;
                for (int i = 0; i < 300; i++)
                {
                    line2[i] = '\0';
                }
                fgets(line2, 300, file2);
                strcat(answer, line2);
            }
            char buffer[200] = {};
            sprintf(buffer, ">>>>>>>>>>>> %d - %d >>>>>>>>>>>>\n%s", buff, counter2, answer);
            strcat(ans, buffer);
            // printf(">>>>>>>>>>>> %d - %d >>>>>>>>>>>>\n%s", buff, counter2, ans);
        }

        strcat(ans, "\n");
        // printf("\n");
        fclose(file1);
        fclose(file2);
    }
}

void undo(char *dir)
{
    FILE *file = fopen(dir + 1, "w");

    int counter = 0;
    int len = strlen(dir);
    while (dir[len - 1 - counter] != '/')
    {
        counter++;
    }
    char buff[50] = {};
    strncat(buff, dir, len - counter);
    strcat(buff, ".");
    strcat(buff, dir + len - counter);
    FILE *copy = fopen(buff + 1, "r");

    char c;
    c = fgetc(copy);
    while (c != EOF)
    {
        fprintf(file, "%c", c);
        c = fgetc(copy);
    }
    fclose(file);
    fclose(copy);
}

int main()
{
    clear();
    input();
    while (strcmp(s[0], "exit") != 0)
    {
        clearans();
        f = 0;

        arman = 0;
        int COUNTER = 0;
        while (s[COUNTER][0] != '\0')
        {
            if (strcmp(s[COUNTER], "=D") == 0)
            {
                arman = COUNTER;
            }
            COUNTER++;
        }

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

        else if (strcmp(s[0], "grep") == 0) // grep
        {

            int mode;
            int answer;
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
                    answer += grep(s[2 + plus], s[4 + plus + counter], mode);
                    counter++;
                }
                if (mode == 3)
                {
                    clearans();
                    char buff[50] = {};
                    sprintf(buff, "%d\n", answer);
                    strcat(ans, buff);
                    // printf("%d\n", answer);
                }
            }
        }

        else if (strcmp(s[0], "find") == 0) // find
        {
            int start = 0;
            int mode = 0;
            int corw = 0;
            int flag = 0;
            for (int i = 5; s[i][0] != '\0'; i++)
            {
                if (strcmp(s[i], "-at") == 0)
                {
                    i++;
                    start = change(s[i]);
                }
                if (strcmp(s[i], "-count") == 0)
                {
                    if (mode == 0 && start == 0)
                    {
                        mode = 1;
                    }
                    else
                    {
                        printf("Invalid input.\n");
                        flag = 1;
                    }
                }
                if (strcmp(s[i], "-all") == 0)
                {
                    if (mode == 0 && start == 0)
                    {
                        mode = 2;
                    }
                    else
                    {
                        printf("Invalid input.\n");
                        flag = 1;
                    }
                }
                if (strcmp(s[i], "-byword") == 0)
                {
                    corw = 1;
                }
            }

            if (strcmp(s[1], "-str") != 0 || strcmp(s[3], "-file") != 0)
            {
                printf("Invalid input.\n");
            }
            else if (flag == 0)
            {
                find(corstr(s[2]), corstr(s[4]), mode, start, corw);
            }
        }

        else if (strcmp(s[0], "replace") == 0) // find
        {
            int start = 0;
            int mode = 0;
            int flag = 0;
            for (int i = 7; s[i][0] != '\0'; i++)
            {
                if (strcmp(s[i], "-at") == 0)
                {
                    if (mode == 1)
                    {
                        printf("Invalid input.\n");
                        flag = 1;
                    }
                    else
                    {
                        i++;
                        start = change(s[i]);
                    }
                }

                if (strcmp(s[i], "-all") == 0)
                {
                    if (mode == 0 && start == 0)
                    {
                        mode = 1;
                    }
                    else
                    {
                        printf("Invalid input.\n");
                        flag = 1;
                    }
                }
            }

            if (fopen(s[6] + 1, "r") != 0) // check file
            {
                createcopy(s[6]);
                f = 1;
            }

            if (strcmp(s[1], "-str1") != 0 || strcmp(s[3], "-str2") != 0 || strcmp(s[5], "-file") != 0)
            {
                printf("Invalid input.\n");
            }
            else if (flag == 0)
            {
                int ans = 1;
                if (mode == 0) // mode 0
                {
                    ans = replace(corstr(s[2]), corstr(s[6]), start, corstr(s[4]));
                }
                else // mode all
                {
                    while (ans == 1)
                    {
                        ans = replace(corstr(s[2]), corstr(s[6]), 0, corstr(s[4]));
                    }
                }
            }
        }

        else if (strcmp(s[0], "tree") == 0) // tree
        {
            clearans();
            dcounter = 0;
            depth = change(s[1]);
            if (depth == -1)
            {
                depth = 20;
                tree("root", 0);
            }
            else if (depth < -1)
            {
                printf("Invalid input.\n");
            }
            else
            {
                tree("root", 0);
            }
        }

        else if (strcmp(s[0], "auto-indent") == 0) // closing pairs
        {
            autoindent(s[1]);
        }

        else if (strcmp(s[0], "compare") == 0)
        {
            compare(s[1], s[2]);
        }

        else if (strcmp(s[0], "undo") == 0)
        {
            if (strcmp(s[1], "-file") != 0)
            {
                printf("Invalid input.\n");
            }
            else
            {
                undo(corstr(s[2]));
            }
        }

        else if (strcmp(s[0], "exit") != 0) // invalid input // when enter in inputed bug happens
        {
            printf("Invalid input!\n");
        }

        if (arman == 0)
        {
            printf("%s", ans);
            clear();
            input();
        }
        else
        {
            arman++;
            if (strcmp(s[0 + arman], "insertstr") == 0) // insertstr
            {

                if (strcmp(s[1 + arman], "-file") != 0 || strcmp(s[3 + arman], "-pos") != 0)
                {
                    printf("Invalid input.\n");
                }
                else
                {
                    insertstr(corstr(s[2 + arman]), ans, pos(s[4 + arman], 1), pos(s[4 + arman], 2)); // need to make pos function
                }
            }

            else if (strcmp(s[0 + arman], "find") == 0) // find
            {
                int start = 0;
                int mode = 0;
                int corw = 0;
                int flag = 0;
                for (int i = 3 + arman; s[i][0] != '\0'; i++)
                {
                    if (strcmp(s[i], "-at") == 0)
                    {
                        i++;
                        start = change(s[i]);
                    }
                    if (strcmp(s[i], "-count") == 0)
                    {
                        if (mode == 0 && start == 0)
                        {
                            mode = 1;
                        }
                        else
                        {
                            printf("Invalid input.\n");
                            flag = 1;
                        }
                    }
                    if (strcmp(s[i], "-all") == 0)
                    {
                        if (mode == 0 && start == 0)
                        {
                            mode = 2;
                        }
                        else
                        {
                            printf("Invalid input.\n");
                            flag = 1;
                        }
                    }
                    if (strcmp(s[i], "-byword") == 0)
                    {
                        corw = 1;
                    }
                }

                if (strcmp(s[1 + arman], "-file") != 0)
                {
                    printf("Invalid input.\n");
                }
                else if (flag == 0)
                {
                    find(ans, corstr(s[2 + arman]), mode, start, corw);
                }
            }

            else if (strcmp(s[0 + arman], "grep") == 0) // grep
            {

                int mode;
                int answer;
                int plus;
                int counter = 0;
                if (strcmp(s[1 + arman], "-l") == 0) // mode 2
                {
                    mode = 2;
                    plus = 1;
                }
                else if (strcmp(s[1 + arman], "-c") == 0) // mode 3
                {
                    mode = 3;
                    plus = 1;
                }
                else // mode 1
                {
                    mode = 1;
                    plus = 0;
                }
                if (strcmp(s[1 + plus + arman], "-files") != 0)
                {
                    printf("Invalid input.\n");
                }
                else
                {
                    while (s[2 + plus + counter + arman][0] != '\0')
                    {
                        answer += grep(ans, s[2 + plus + counter + arman], mode);
                        counter++;
                    }
                    if (mode == 3)
                    {
                        clearans();
                        char buff[50] = {};
                        sprintf(buff, "%d\n", answer);
                        strcat(ans, buff);
                        // printf("%d\n", ans);
                    }
                }
            }

            else
            {
                printf("Invalid input.\n");
            }
        }
    }
}