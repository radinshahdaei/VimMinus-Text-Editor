#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int sn(char *s)
{
    if (s[0] == 92 && s[1] == 'n')
    {
        return 1;
    }
    return 0;
}

int snn(char *s)
{
    if (s[0] == 92 && s[1] == 92 && s[2] == 'n')
    {
        return 1;
    }
    return 0;
}

int ss(char *s)
{
    if (s[0] == 92 && s[1] == '*')
    {
        return 1;
    }
    return 0;
}

int sq(char *s)
{
    if (s[0] == 92 && s[1] == '"')
    {
        return 1;
    }
    return 0;
}

void remq(char *s)
{
    int len = strlen(s);
    if (s[0] == '"' && s[len - 1] == '"')
    {
        for (int i = 0; i < len - 1; i++)
        {
            s[i] = s[i + 1];
        }
        s[len - 2] = '\0';
        s[len - 1] = '\0';
    }
}

char *corstr(char *s)
{
    int len = strlen(s);
    remq(s);
    for (int i = 0; i < len; i++)
    {
        if (snn(&s[i])) // for \\n
        {
            for (int j = i; j < len; j++)
            {
                s[j] = s[j + 1];
            }
        }
        else if (sn(&s[i])) // for \n
        {
            s[i] = '\n';
            for (int j = i + 1; j < len; j++)
            {
                s[j] = s[j + 1];
            }
        }
        else if (sq(&s[i])) // for \"
        {
            s[i] = '"';
            for (int j = i + 1; j < len; j++)
            {
                s[j] = s[j + 1];
            }
        }
    }
    return s;
}

char *get_string(char *string)
{
    int counter = 0;
    char flag = 'T';
    string[counter] = getchar();
    counter++;
    while (flag == 'T')
    {
        string[counter] = getchar();
        if (string[counter] == '"' && string[counter - 1] != 92)
        {
            flag = 'F';
        }
        counter++;
    }
    return string;
}

int change(char *string)
{
    int len = strlen(string);
    int ans = 0;
    if (string[0] == '-')
    {
        for (int i = 1; i < len; i++)
        {
            ans = ans * 10 - (string[i] - 48);
        }
    }
    else
    {

        for (int i = 0; i < len; i++)
        {
            ans = ans * 10 + (string[i] - 48);
        }
    }
    return ans;
}

int pos(char *string, int mode)
{
    int len = strlen(string);
    int ans = 0;
    int a;
    if (mode == 1)
    {
        int counter = 0;
        while (string[counter] != ':')
        {
            ans = ans * 10 + (string[counter] - 48);
            counter++;
        }
    }
    if (mode == 2)
    {
        int counter = len - 1;
        while (string[counter] != ':')
        {
            a = (string[counter] - 48);
            ans = ans + a * (int)pow(10, len - counter - 1);
            counter--;
        }
    }
    return ans;
}

int findinline(char *s, char *pat)
{
    int counter = 0;
    int pcounter = 0;
    int len = strlen(pat);
    char *st = malloc((len) * sizeof(char));
    while (s[counter] != '\0')
    {
        strncpy(st, &s[counter], len);
        if (strcmp(pat, st) == 0)
        {
            pcounter++;
        }
        counter++;
    }
    return pcounter;
}

int match(char *first, char *second)
{

    if (*first == '\0' && *second == '\0')
        return 1;

    if (*first == '*')
    {
        while (*(first + 1) == '*')
            first++;
    }

    if (*first == '*' && *(first + 1) != '\0' && *second == '\0')
        return 0;

    if (*first == 92 && *(first + 1) == '*' && *second == '*') // lets test
    {
        return match(first + 2, second + 1);
    }
    if (*first == '?' || *first == *second)
        return match(first + 1, second + 1);

    if (*first == '*')
        return match(first + 1, second) || match(first, second + 1);
    return 0;
}

int findin(char array[], char pat[])
{

    int flag = 0;

    int len = strlen(pat);
    int arrlen = strlen(array) - len;

    for (int i = 0; i < arrlen; i++)
    {

        char string[50] = {};
        strncpy(string, array + i, len);

        if (match(pat, string) == 1)
        {
            flag = 1;
        }
    }
    return flag;
}

char *makestr(char *s)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (ss(&s[i])) // for \*
        {
            for (int j = i; j < len; j++)
            {
                s[j] = s[j + 1];
            }
        }
    }
    return s;
}