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
    int changeint = round(change*100);

    int q = 0;
    int d = 0;
    int n = 0;
    int p = 0;

    while (q*25 < changeint && (q+1)*25 <= changeint) {
        q++;
    };
    changeint = changeint - q*25;

    while (d*10 < changeint && (d+1)*10 <= changeint) {
        d++;
    };
    changeint = changeint - d*10;

    while (n*5 < changeint && (n+1)*5 <= changeint) {
        n++;
    };
    changeint = changeint - n*5;

    while (p*1 < changeint && (p+1)*1 <= changeint) {
        p++;
    };
    changeint = changeint - p*1;

    int out = q + d + n + p;
    printf("%i\n", out);
}
