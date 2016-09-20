#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // initializes two variables
    // height - height of the pyramid
    // j - counter used for the loop
    int height, j = 2;

    /*GetInt() has auto-check for strings and floats, but we still need
    to check for numbers less than 0 or greater than 23.*/
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);

    // the main loop; counters used are i, j, k, and l
    for (int i = 1; i <= height && j <= height + 1; i++)
    {
        // spaces
        for (int l = height; l >= j; l--)
        {
            printf(" ");
        }
        // hashtags
        for (int k = 1; k <= j; ++k)
        {
            printf("#");
        }
        j++;
        printf("\n");
    }
}
