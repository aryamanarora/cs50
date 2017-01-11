/**
 * initials.c
 *
 * Computer Science 50
 * Problem Set 2
 *
 * Finds the initials of a given name.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // prompts for name, gets length; max length 512
    char* name;
    fgets(name, 512, stdin);
    int namelength = strlen(name);

    // scan through letters, prints them if the previous letter was a space
    for (int i = 0; i < namelength; i++)
    {
        if (name[i] != ' ' && name[i - 1] == ' ')
        {
            char initial = toupper(name[i]);
            printf("%c", initial);
        }
    }

    // newline
    printf("\n");

    return 0;
}
