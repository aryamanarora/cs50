/**
 * Finds the difference between (1 + 2 + ... + 100)^2 and 1^2 + 2^2 ... + 100^2.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    long long wholesquare = (100 + 1) * 50;
    wholesquare = wholesquare * wholesquare;

    long long squarea = 0;
    long long squarefin = 0;

    for (int i = 1, j = 1; i <= 100; i++)
    {
        squarea += j;
        squarefin += squarea;
        j += 2;
    }

    long long result = wholesquare - squarefin;
    printf("%lld\n", result);
}
