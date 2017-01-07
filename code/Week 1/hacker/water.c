#include <stdio.h>

int main(void)
{
    // get minutes
    int minutes;
    printf("Minutes: ");
    scanf("%i", &minutes);

    while (minutes < 0)
    {
        printf("Retry:");
        scanf("%i", &minutes);
    }

    // print bottles
    int bottles = minutes * 12;
    printf("Bottles: %i\n", bottles);
}
