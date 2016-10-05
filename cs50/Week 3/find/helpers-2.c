/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include <math.h>

#include "helpers.h"

/**
 * DIVIDE-AND-CONQUER SEARCH
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n == 1 && values[0] == value)
    {
        return true;
    }

    int midpoint = (n + (n % 2))/2;
    int midnumber = values[midpoint];
    int startpoint = 0;

    for (int i = 0; i < log2(n) + 1; i++)
    {
        if (value < midnumber)
        {
            midpoint = startpoint + ((midpoint - startpoint) - ((midpoint - startpoint) % 2))/2;
            midnumber = values[midpoint];

        }
        else if (value > midnumber)
        {
            startpoint = midpoint + 1;
            midpoint = midpoint + ((n - startpoint) + ((n - startpoint) % 2))/2;
            midnumber = values[midpoint];
        }
        else if (value == midnumber)
        {
            printf("%i, %i, %i\n", startpoint,midpoint,midnumber);
            return true;
        }
        else
        {
            printf("%i, %i, %i\n", startpoint,midpoint,midnumber);
            return false;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // initialize storage variable
    int storage;
    // This loop compares all the variables with the next variable (n - 1 comparisions)
    // n times, and sorts the array with bubble sort.
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {

            if (values[i] > values[i + 1] && i + 1 < n)
            {
                storage = values[i];
                values[i] = values[i + 1];
                values[i + 1] = storage;
            }
        }
    }
}
