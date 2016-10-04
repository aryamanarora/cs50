/**
 * Implements the Caesar cipher.
 */

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
        printf("Pass the key number! Ex: ./caesar 13.\n");
    }

    // ask for message that will be encoded
    string message = GetString();

    // stores the length of the message for future reference
    int length = strlen(message);

    // makes sure argv[1] is readable by the code; also does modulo 26
    int k = atoi(argv[1]);
    k = k % 26;

    // initializes global char "c" for use in the loop
    char c;

    // goes through each individual character and encodes
    for (int i = 0; i < length; i++)
    {
        // if the current char is uppercase AND might output
        // a wrong value when k is added, cycle from Z to A
        if (message[i] <= 90 && message[i] >= 65 && message[i] + k > 90)
        {
            c = 64 + ((message[i] + k) - 90);
        }
        // if the current char is lowercase " "
        else if (message[i] <= 122 && message[i] >= 97 && message[i] + k > 122)
        {
            c = 96 + ((message[i] + k) - 122);
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
            c = message[i] + k;
        }
        // print the character
        printf("%c",c);
    }

    // new line to end program
    printf("\n");
}
