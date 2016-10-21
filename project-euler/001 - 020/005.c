/**
 * Finds the lowest common denominator of 1 through 20.
 */

#include <stdio.h>
#include <stdlib.h>

int lcm(int a, int b);

int main(int argc, char const *argv[])
{
    int result = 2520; // 2520 = lcm(1 through 10)
    for (int i = 11; i <= 20; i++)
    {
        if (result % i != 0)
        {
            result = lcm(i, result);
        }
    }
    printf("%i\n", result);
    return 0;
}

int lcm(int a, int b)
{
    // b should be the bigger number
    for (int i = b; i <= a * b; i++)
    {
        if (i % b == 0 && i % a == 0)
        {
            return i;
        }
    }
    return a * b;
}
