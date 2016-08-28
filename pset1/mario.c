#include <stdio.h>
#include <cs50.h>

int getHeight(void);
void repeatPrint(char, int);

int main(void)
{
    // stores the height of the pyramid:
    int height = 0;
    height = getHeight();

    // looping to draw each lever of the pyramid.
    for(int k = 1; k <= height; k++)
    {
        // drawing spaces.
        repeatPrint(' ', height - k);
        // drawing bricks.
        repeatPrint('#', k + 1);
        repeatPrint('\n', 1);
    }

}

// gets the height from the user.
// ensures that the hight is positive number.
int getHeight(void)
{
    int input = -1;
    while (input < 0 || input > 23)
    {
        printf("Height: ");
        input = GetInt();
    }
    return input;
}

// prints "letter" with "repeates" times;
void repeatPrint(char letter, int repeats)
{
    for (int i = 0; i < repeats; i++)
        printf("%c", letter);
}
