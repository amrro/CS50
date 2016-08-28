
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // amount of times spent in the shower:
    int period = 0;
    printf("minutes: ");
    period = GetInt();

    // handles if the number is less than zero.
    // there is no negative numbers for time.
    while (period < 0)
    {
        printf("Retry: ");
        period = GetInt();
    }

    // outputs the final number of bottles used.
    printf("bottles: %i\n", period * 12);
}
