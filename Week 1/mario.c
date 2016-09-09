#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, j = 2;
    do
    {
        printf("Height: "); //prompt for height
        height = GetInt();
    }
    while (height < 0 || height > 23); //GetInt has auto-check

    for (int i = 1; i <= height && j <= height + 1; i++)
    {
        for (int l = height; l >= j; l--)
        {
            printf(" ");
        }
        for (int k = 1; k <= j; ++k)
        {
            printf("#");
        }
        j++;
        printf("\n");
    }
}
