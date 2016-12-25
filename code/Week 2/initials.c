/**
 * initials.c
 *
 * Computer Science 50
 * Problem Set 2
 *
 * Finds the initials of a given name.
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // prompts for name, gets length
    string name = GetString();
    int namelength = strlen(name);

    // first letter is always an initial; make the first letter uppercase
    char firstinitial = toupper(name[0]);
    // print first letter of the name
    printf("%c", firstinitial);

    // scan through letters until a space is found,
    // then prints the next letter in uppercase
    for (int i = 0; i < namelength; i++)
    {
        if (name[i] == 32)
        {
            char initial = toupper(name[i + 1]);
            printf("%c",initial);
        }
    }

    // newline
    printf("\n");
}
