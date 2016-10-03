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

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // if the array is of negative size, return false
    if (n < 1)
    {
        return false;
    }

    // search linearly; examine each value for number
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
        {
            return true;
        }
        else if (i == n - 1 && values[i] != value)
        {
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
    int storage;
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
