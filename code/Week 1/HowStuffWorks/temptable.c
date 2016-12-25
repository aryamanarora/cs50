/**
 * temptable.c
 *
 * Computer Science 50
 * Week 1
 */

#include <stdio.h>

int main(void)
{
    // initialize variables
    float min, max, inc;

    // get minimum for table columns
    printf("Minimum? ");
    scanf("%f", &min);
    printf("\n");

    // get maximum for table
    printf("Maximum? ");
    scanf("%f", &max);
    printf("\n");

    // get incrememnt for table
    printf("Increment? ");
    scanf("%f", &inc);
    printf("\n");

    // some variables
    float a, b;
    a = min;
    b = -1;

    // print the table
    printf("FAHRENHEIT TO CELSIUS TABLE\n");

    while (a <= max)
    {
        // handle 98.6 degrees always
        if ((a > 98.6) && (b < 98.6))
        {
            printf("%6.2f degrees F = %6.2f degrees C\n", 98.6, (98.6 - 32.0) * 5.0 / 9.0);
        }

        // other degrees
        printf("%6.2f degrees F = %6.2f degrees C\n", a, (a - 32.0) * 5.0 / 9.0);
        b = a;
        a = a + inc;
    }

    // bye!
    return 0;
}
