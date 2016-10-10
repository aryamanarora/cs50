#include <stdio.h>

int lcm(int x, int y);

int main(void)
{
    long long result;
    long long j = 1;

    for (long long i = 1; i <= 20; i++) {
        j = result;
        result = lcm(j, i + 1);
    }

    printf("%lli\n", result);
}

int lcm(int x, int y)
{
    static long long j = 1;

    if (j % x == 0 && j % y == 0)
    {
        return j;
    }

    j++;
    lcm(x, y);
    return j;
}
