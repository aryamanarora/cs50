#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int min = GetInt() * 12;
    printf("bottles: %i\n", min);
}
