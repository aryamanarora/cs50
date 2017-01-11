/**
 * add2.c
 *
 * Computer Science 50
 * Week 1
 *
 * Adds two user inputted numbers.
 */

#include <stdio.h>

int main()
{
    // initialize variables
    int a, b, c;

    // get variables from the user
    printf("Enter the first value:");
    scanf("%d", &a);
    printf("Enter the second value:");
    scanf("%d", &b);

    // add them and print
    c = a + b;
    printf("%d + %d = %d\n", a, b, c);
    
    return 0;
}
