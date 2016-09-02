#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 * amr elghobary
 */

#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // to hold the jped file's name.
    char* filename = malloc(7 * sizeof(char));

    // open the card.raw file.
    FILE *card = fopen("card.raw", "r");

    // ensure card is opend.
    if (card == NULL)
    {
        printf("Couldn't open the file.\n");
        return 1;
    }

    // to open jpeg file to write data into.
    FILE *jpegFile = NULL;

    // Block = 512B.
    BYTE *block = malloc(BLOCK * sizeof(BYTE));

    // save the number of jpeg files found.
    int jpegNum = 0;

    // read Block by Block for the card memory.
    while (fread(block, BLOCK * sizeof(BYTE), 1, card) == 1)
    {
        if ((block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff) &&
                (block[3] == 0xe0 || block[3] == 0xe1))
        {
            // increase jpeg found by one.
            sprintf(filename, "%03d.jpg", jpegNum++);

            if (jpegFile == NULL)
            {
                jpegFile = fopen(filename, "w");
            }
            else
            {
                fclose(jpegFile);
                jpegFile = fopen(filename, "w");
            }

            // if jpegFile still NULL, there is an error.
            if (jpegFile == NULL)
            {
                printf("Error in creating #%s file!\n", filename);
                break;
            }
            fwrite(block, BLOCK * sizeof(BYTE), 1, jpegFile);
            continue;
        }

        if (jpegFile != NULL)
            fwrite(block, BLOCK * sizeof(BYTE), 1, jpegFile);

    }

    printf("JPEG found: %i\n", jpegNum);

    // free filename from data.
    if (filename != NULL)
        free(filename);

    if (block != NULL)
        free(block);

    if (jpegFile != NULL)
        free(jpegFile);
    return 0;

}
