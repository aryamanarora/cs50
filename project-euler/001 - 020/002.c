/**
 * Finds the sum of the even Fibonacci numbers that are less than 4 million.
 */

#include <stdio.h>

int main(void)
{
    int termi0 = 1;
    int termi = 2;
    int termsum = 0;

    for (int i = 2; i < 10000; i++)
    {
        if (termi % 2 == 0 && termi < 4000000)
        {
            termsum = termsum + termi;
        }
        else if (termi >= 4000000)
        {
            break;
        }

        termi = termi + termi0;
        termi0 = termi - termi0;
    }

    printf("%i\n", termsum);
    return 0;
}
