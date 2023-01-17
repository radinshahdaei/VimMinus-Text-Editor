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
    for (int i = 0; i < len; i++)
    {
        ans = ans * 10 + (string[i] - 48);
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