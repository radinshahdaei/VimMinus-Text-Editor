#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char string[100] = {};
void clear() // clear string
{
    for (int i = 0; i < 100; i++)
    {
        string[i] = '\0';
    }
}
void remq(char string[]) // remove quotation
{
    int len1 = strlen(string);
    for (int i = 0; i < len1 - 1; i++)
    {
        string[i] = string[i + 1];
    }
    string[len1 - 2] = '\0';
    string[len1 - 1] = '\0';
}

void createfile() // createfile
{
    char buff[100] = {};

    char *add = "/Users/Radin/School/Programming/project-radinshahdaei"; // current directory address
    char address[200];
    int addlen = strlen(add);

    scanf("%[^\n]", string); // string input
    int len = strlen(string);

    if (string[0] == '"' && string[len - 1] == '"') // check for quotes
    {
        printf("1\n");
        remq(string);
        len = strlen(string);
    }

    if (string[0] == '"' ^ string[len - 1] == '"' == 1) // check for error
    {
        printf("Invalid input.\n");
    }

    else
    {
        for (int i = 1; i < len; i++) // creating directory
        {
            buff[i - 1] = string[i];
            if (string[i + 1] == '/')
            {
                mkdir(buff, 0777);
            }
        }

        for (int i = 0; i < addlen; i++) // creating address for file
        {
            address[i] = add[i];
        }
        for (int i = 0; i < len; i++)
        {
            address[addlen + i] = string[i];
        }

        FILE *file; // check file
        if (fopen(address, "r") == 0)
        {
            file = fopen(address, "w");
        }
        else
        {
            printf("File already exists.\n");
        }
        fclose(file);
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
                createfile();
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