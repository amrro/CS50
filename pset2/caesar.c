#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// number of the alphabets in english.
#define LETTERS 26

char encrypt(char letter, int key);

int main(int argc, char* argv[])
{
    // validating the user enters the right command.
    if (argc != 2 || argv[1] < 0)
    {
        printf("USAGE: ./casear [positive integer key]\n");
        return 1;
    }
    
    // converting the key to int.
    int key = atoi(argv[1]);
    // prompt the user to enter the text to encrypt.
    string text = GetString();
    
    // looping over the text and output the result.
    for (int i = 0, length = strlen(text); i < length; i++)
        if (isalpha(text[i]))
            printf("%c", encrypt(text[i], key) );
        else
            printf("%c", text[i]);

    printf("\n");
    return 0;
}

/*
 * shifts letter by amount of the passed key.
 */
char encrypt(char letter, int key)
{
    if (isupper(letter))
    {
        int decrypted = ((((letter - 'A') + key) % LETTERS) + 'A');
        return (char) decrypted;
    }

    return (char) ((((letter - 'a') + key) % LETTERS) + 'a');
}
