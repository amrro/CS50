#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define LETTERS 26
char encrypt(char letter, int key);

int main(int argc, char* argv[])
{
    if (argc != 2 || argv[1] < 0)
    {
        printf("USAGE: ./casear [positive integer key]\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string text = GetString();
    for (int i = 0, length = strlen(text); i < length; i++)
        if (isalpha(text[i]))
            printf("%c", encrypt(text[i], key) );
        else
            printf("%c", text[i]);

    printf("\n");
    return 0;
}

char encrypt(char letter, int key)
{
    if(isupper(letter))
    {
        int decrypted = ((((letter - 'A') + key) % LETTERS) + 'A');
        return (char) decrypted;
    }

    return (char) ((((letter - 'a') + key) % LETTERS) + 'a');
}
