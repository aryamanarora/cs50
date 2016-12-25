/**
 * water.c
 *
 * Computer Science 50
 * Problem Set 1
 *
 * How much water do you use in the shower? Let's find out!
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks for minutes of shower time, returns number of bottles of water used
    printf("minutes: ");
    int min = GetInt() * 12;
    printf("bottles: %i\n", min);
}
