/* in progress */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checks if only 1 argument has been passed
    if (argc != 2)
    {
        // if too many or too few arguments are passed, yell
        return 1;
    }

    // ask for message that will be encoded
    string message = GetString();

    // stores the length of the message for future reference
    int length = strlen(message);

    // makes sure argv[1] is readable by the code
    int key[strlen(argv[1])];
    int keylength = strlen(argv[1]);

    // makes the array "key" that is a set of integers corresponding to kj in Vigenere
    for (int i = 0; i < keylength; i++)
    {
        key[i] = argv[1][i];
        if (argv[1][i] > 64 && argv[1][i] < 91)
        {
            key[i] = argv[1][i] - 65;
        }
        else if (argv[1][i] > 96 && argv[1][i] < 123)
        {
            key[i] = argv[1][i] - 97;
        }
        else
        {
            key[i] = 0;
        }
    }

    // make a new extended key that is the key repeating
    int extendedkey[length];
    for (int i = 0; i < length; i++)
    {
        extendedkey[i] = key[i % keylength];
    }

    // initializes global char "c" for use in the loop
    char c;

    // goes through each individual character and encodes
    for (int i = 0; i < length; i++)
    {
        // if the current char is uppercase AND might output
        // a wrong value when k is added, cycle from Z to A
        if (message[i] <= 90 && message[i] >= 65 && message[i] + extendedkey[i] > 90)
        {
            c = 64 + ((message[i] + extendedkey[i]) - 90);
        }
        // if the current char is lowercase " "
        else if (message[i] <= 122 && message[i] >= 97 && message[i] + extendedkey[i] > 122)
        {
            c = 96 + ((message[i] + extendedkey[i]) - 122);
        }
        // if the current char is not a letter, do nothing
        else if (message[i] < 65 || message[i] > 122)
        {
            c = message[i];
        }
        else if (97 > message[i] && message[i] > 90)
        {
            c = message[i];
        }
        // if nothing weird will happen, just add k
        else
        {
            c = message[i] + extendedkey[i];
        }
        // print the character
        printf("%c",c);
    }

    // new line to end program
    printf("\n");
}
