#include <stdio.h>
#include <cs50.h>
#include <math.h>

// defining constants for differnt kind of coins
#define QUARTER 25
#define DIME 10
#define NICKLE 5
#define PENNY 1

// functions declration.
float getChange(void);
int getNumCoins(int*, const int);

int main(void)
{
    printf("How much change is owed?\n");
    int change = round(GetFloat() * 100);
    // ensuring that input is positive number.
    while (change < 0)
    {
        printf("How much change is owed?\n");
        change = round(GetFloat()) * 100;
    }

    // count number coin for each type of change coin.
    int numCoins = getNumCoins(&change, QUARTER);
    numCoins += getNumCoins(&change, DIME);
    numCoins += getNumCoins(&change, NICKLE);
    numCoins += getNumCoins(&change, PENNY);

    // output:
    printf("%i\n", numCoins);

    return 0;
}

// calculates the number of change coins needed for each change.
// REMEMBER: changes the value of passed change.
int getNumCoins(int *change, const int coin)
{
    int num = (int) *change / coin;
    *change = *change - (num * coin);
    return num;
}
