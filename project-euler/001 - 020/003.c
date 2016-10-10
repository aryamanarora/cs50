/**
 * A program that finds the prime factors of a number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    long long num = atoll(argv[1]);
    long long factor;

    while (num % 2 == 0)
    {
        num = num / 2;
        factor = 2;
        printf("%lli\n", factor);
    }

    long long i = 3;

    for (int j = 0; j < 100000; j++, i = i + 2)
    {
        while (num % i == 0)
        {
            num = num / i;
            factor = i;
            printf("%lli\n", factor);
        }

        if (num == 1)
        {
          break;
        }
    }
}
