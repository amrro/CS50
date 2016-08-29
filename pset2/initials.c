#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>


int main(void)
{

    string name = GetString();

    for (int i = 0, n = strlen(name); i < n - 1; i++)
        if ( name[i] == ' ')
            printf("%c", toupper(name[i + 1]));
        else if (i == 0)
            printf("%c", toupper(name[i]));

    printf("\n");
    return 0;
}
