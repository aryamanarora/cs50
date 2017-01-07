/**
 * credit.c
 *
 * Computer Science 50
 * Problem Set 1 Hacker Edition
 *
 * Finds out credit card type and validity.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 16

int main(void)
{
    // get number
    long long card;
    scanf("%lli", &card);

    // check if it is positive
    if (card < 0)
        return 1;

    // convert int card to char[]
    char card_string[(int)((ceil(log10(card))+1)*sizeof(char))];
    sprintf(card_string, "%lli", card);
    size_t card_len = strlen(card_string);

    // Luhn's algorithm
    bool is_valid = false;
    bool every_other = false;
    long long check = 0;

    for (int i = card_len - 1; i >= 0; i--)
    {
        // ternary operator magic
        long long digit = every_other ? (card_string[i] - '0') * 2 : (card_string[i] - '0');
        check += digit >= 10 ? (digit % 10) + (digit / 10) : digit;

        every_other = !every_other;
    }

    is_valid = (check % 10 == 0);

    if (is_valid)
    {
        // credit card type
        if (card_len == 15 && card_string[0] == '3' && (card_string[1] = '7' || card_string[0] == '4'))
        {
            printf("AMEX\n");
        }
        else if ((card_len == 13 || card_len == 16) && card_string[0] == '4')
        {
            printf("VISA\n");
        }
        else if (card_len == 16 && card_string[0] == '5' && ((card_string[1] - '0') > 0 && (card_string[1] - '0') < 5))
        {
            printf("MASTERCARD\n");
        }
    }
    else
        printf("INVALID\n");

    return 0;
}
