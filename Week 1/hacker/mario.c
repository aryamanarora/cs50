#include <stdio.h>

int main(void)
{
    // get height and validate
    int height;
    printf("Height: ");
    scanf("%i", &height);

    while(height < 0 || height > 23)
    {
        printf("Retry:");
        scanf("%i", &height);
    }

    // print
    for (int spaces = height - 1; spaces >= 0; spaces--)
    {
        for (int i = 0; i < spaces; i++)
            printf(" ");

        for (int j = 0; j < height - spaces; j++)
            printf("#");

        printf(" ");

        for (int j = 0; j < height - spaces; j++)
            printf("#");

        printf("\n");
    }
}
