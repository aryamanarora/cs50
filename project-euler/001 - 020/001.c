/**
 * Finds the sum of all multiples of 3 or 5 that are lesss than 1000.
 */

#include <stdio.h>

int main(void)
{
    int sum;

    for (int i = 1; i < 1000; i++)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            sum = sum + i;
        }
    }

    printf("%i\n", sum);
    return 0;
}
