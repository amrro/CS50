/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

bool BinarySearch(int value, int values[], int left, int right)
{
    // THE END CONDITION.
    if (!(left <= right))
        return false;

    // find the midpoint
    int midpoint = (left + right) / 2;

    // if value < middle point move to left subset.
    if (value < values[midpoint])
        return BinarySearch(value, values, left, midpoint - 1);

    // if value > middle point move to right subset.
    else if (value > values[midpoint])
        return BinarySearch(value, values, midpoint + 1, right);

    // else vlaue == middle point, return TRUE.
    else
        return true;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    return BinarySearch(value, values, 0, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // TODO: implementing selection sort.
    // remember the smallest index.
    int smallest = 0;
    // for swap's sake.
    int temp = 0;
    for (size_t i = 0; i < n; i++)
    {
        smallest = i;
        // find the smallest element in the unsorted part.
        for (size_t j = i + 1; j < n; j++)
            if (values[smallest] > values[j])
                smallest = j;
        temp = values[i];
        values[i] = values[smallest];
        values[smallest] = temp;
    }
    return;
}
