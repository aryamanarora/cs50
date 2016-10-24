/**
 * Implements greedy algorithm, to find minimum number of coins needed for a
 * certain dollar value.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;

    do
    {
        printf("Hello! How much change is owed?\n");
        change = GetFloat();
    }
    while (change <= 0);

    // converts float to int by multiplying by 100 and rounding
    int changeint = round(change * 100);

    // initalizes four variables for quarters, nickels, dimes, and pennies
    int q = 0;
    int d = 0;
    int n = 0;
    int p = 0;

    /*Four similar sets of code are run below.
    Each one finds the maximum number of coins
    that can be used without giving more change
    than needed. It then subtracts the value of
    these coins from changeint and performs the
    process again for smaller denominations.*/

    while (q * 25 < changeint && (q + 1) * 25 <= changeint)
    {
        q++;
    }

    changeint = changeint - q * 25;

    while (d * 10 < changeint && (d + 1) * 10 <= changeint)
    {
        d++;
    }

    changeint = changeint - d * 10;

    while (n * 5 < changeint && (n + 1) * 5 <= changeint)
    {
        n++;
    }

    changeint = changeint - n * 5;

    while (p < changeint && (p + 1) <= changeint)
    {
        p++;
    }

    // adds the number of quarters, dimes, nickles, and pennies
    int output = q + d + n + p;

    // prints the output :)
    printf("%i\n", output);
}
