/**
 * Finds the 10,001st prime number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int prime (int n);

int main(int argc, char const *argv[])
{
    int results[10001];
    for (int i = 2, j = 0; j <= 10000; i++) {
        if (prime(i) == true)
        {
            results[j] = i;
            j++;
        }
    }
    printf("%i\n", results[10000]);
}

int prime(int n)
{
    if (n == 2)
        return true;
    else if (n <= 1 || n % 2 == 0)
        return false;
    else if (n % 2 != 0)
    {
        for (int i = 3; i <= n / 2; i += 2)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}
