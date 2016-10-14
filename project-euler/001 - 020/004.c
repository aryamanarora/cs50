/**
 * Finds the largest palindrome number that is the product of two three digit numbers.
 */
#include <stdio.h>

int reverse_num(int num);

int main(void)
{
    int answer = 10000;

    for (int i = 100; i < 999; i++)
    {
        for (int j = 100; j < 999; j++)
        {
            if (i * j == reverse_num(i * j) && i * j > answer)
            {
                answer = i * j;
            }
        }
    }
    printf("%i\n", answer);

    return 0;
}

int reverse_num(int num)
{
    int reverse = 0;
    int remaining;

    while (num > 0)
    {
        remaining = num % 10;
        reverse = reverse * 10 + remaining;
        num = num / 10;
    }

    return reverse;
}
