#include <stdio.h>

int main()
{

    float min, max, inc;

    printf("Minimum? ");
    scanf("%f", &min);

    printf("Maximum? ");
    scanf("%f", &max);

    printf("Increment? ");
    scanf("%f", &inc);

    float a, b;
    a = min;
    b = -1;

    printf("FAHRENHEIT TO CELSIUS TABLE\n");

    while (a <= max)
    {
	if ((a > 98.6) && (b < 98.6))
        {
            printf("%6.2f degrees F = %6.2f degrees C\n",
                98.6, (98.6 - 32.0) * 5.0 / 9.0);
        }
        printf("%6.2f degrees F = %6.2f degrees C\n",
            a, (a - 32.0) * 5.0 / 9.0);
        b = a;
        a = a + inc;
    }
    return 0;
}
