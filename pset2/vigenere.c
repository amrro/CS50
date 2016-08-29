#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

// number of letters in the english alphabet
#define ALPHABET 26

char encrypt(char, char);
string encryptText(string, string);


int main(int argc, char *argv[])
{
    // validating the right command.
    if (argc != 2)
    {
        printf("USAGE: ./vigenere [string key]\n");
        return 1;
    }

    string key = (string) argv[1];
    // checking if the key has any non alphabet chars.
    for (int i = 0, n = strlen(key); i < n; i++)
        if (!isalpha(key[i]))
        {
            printf("Key has to be alphabets only!\n");
            return 1;
        }
    // prompt user to enter text after validate key.
    string text = GetString();
    string encrypted = encryptText(text, key);
    // output:
    printf("%s\n", encrypted);
    return 0;
}

/*
 * encrypts the whole text using the keyword passed to it.
 */
string encryptText(string text, string key)
{
    // saves the skip for non alphabetical letters.
    int skips = 0;  
    for (int i = 0, n = strlen(text); i < n; i++)
        if (isalpha(text[i]))
            text[i] = encrypt(text[i], key[(i - skips) % strlen(key)]);
        else
            skips++;
    return text;
}

/*
 * shifts the letter by the amount of the key provided.
 * letter: the letter to be shifted, capital or small.
 * key: an int value to shift the given letter.
 */
char encrypt(char letter, char key)
{
    int code = isupper(key) ? (int) (key - 'A') : (int) (key - 'a');
    return isupper(letter) ? 
            (char) ((((letter - 'A') + code) % ALPHABET) + 'A') :
            (char) ((((letter - 'a') + code) % ALPHABET) + 'a');
}
