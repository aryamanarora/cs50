/**
 * credit.c
 *
 * Computer Science 50
 * Problem Set 1 Hacker Edition
 *
 * Finds out credit card type and validity. **DOES NOT WORK**
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 16

// TODO: fix this
bool validate(long long card)
{
    // convert to array
    char card_string[MAX_LEN + 1];
    sprintf(card_string, "%lli", card);
    printf("%s", card_string);

    // get sum of every other digit
    int sum = 0;
    for (int i = 0; i < MAX_LEN; i++)
    {
        if (i % 2 == 1)
        {
            int t = (int) card_string[i], i_sum = 0, remainder;
            while (t != 0)
            {
                 remainder = t % 10;
                 i_sum    += remainder;
                 t         = t / 10;
            }
            printf("%i\n", i_sum);
            sum += i_sum;
        }
    }
    sum *= 2;
    printf("%i\n", sum);

    // add to rest
    for (int j = 0; j < MAX_LEN; j++)
    {
        if (j % 2 == 0)
            sum += ((int) card_string[j]);
    }

    // is it valid?
    if (sum % 10 == 0)
        return true;

    return false;
}

int main(void)
{
    // get card number from stdin
    long long card;
    scanf("%lli", &card);

    // is it a valid number?
    if (validate(card) == false)
    {
        printf("That's no credit card!\n");
    }

    // which kind?
    char card_string[MAX_LEN + 1];
    sprintf(card_string, "%lli", card);

    if (strlen(card_string) == 15 && (card/10000000000000 == 34 || card/10000000000000 == 37))
    {
        printf("That's an AmEx\n");
    }
    else if (strlen(card_string) == 13 && card/1000000000000 == 4)
    {
        printf("That's a Visa\n");
    }
    else if (strlen(card_string) == 16)
    {
        if (card/1000000000000000 == 4)
        {
            printf("That's a Visa\n");
        }
        else if (card/1000000000000000 >= 51 && card/1000000000000000 <= 55)
        {
            printf("That's an AmEx\n");
        }
        else
        {
            printf("What?\n");
        }
    }
    else
    {
        printf("What?\n");
    }

    return 0;
}
