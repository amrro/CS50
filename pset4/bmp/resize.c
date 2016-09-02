//
// Created by amro on 9/1/16.
//
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char* argv[])
{
    /*
    // ensure proper usage.
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    int factor = atoi(argv[1]);

    // ensure factor is postivie and less than 100;
    if (factor < 0)
    {
        printf("n has to be positive number!\n");
        return 2;
    }
    else if (factor > 100)
    {
        printf("n has to be less than or equal 100.\n");
        return 2;
    }

    // saving filenames.
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Couldn't open %s.\n", infile);
        return 2;
    }

    // open outfile.
    FILE *outptr = fopen(outfile, "w+");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Couldn't create %s.\n", outfile);
        return 2;
    }
*/

    int factor = 1;
    FILE *inptr = fopen("small.bmp", "r");
    FILE *outptr = fopen("large.bmp", "w+");


    // read BITMAPFILEHEADER from infile.
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read BITMAPINFOHEADER from infile.
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oldHeight = abs(bi.biHeight);
    int oldWidth = bi.biWidth;


    // TODO: change some of value of outfile to the new size.
    bi.biHeight *= factor;
    bi.biWidth *= factor;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);



    // write BITMAPFILEHEADER to outfile.
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write BITMAPINFOHEADER to outfile
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE *scanline;

    printf("Original biWidth: %d\n", bi.biWidth);
    printf("Original biHeight: %d\n", bi.biHeight);
    printf("Original biSizeImage: %d\n", bi.biSizeImage);
    printf("Original bfSize: %d\n", bf.bfSize);
    printf("Original biSize: %d\n\n", bi.biSize);

    // iterate over infile's scanline.
    for (int height = 0; height < oldHeight; height++)
    {
        scanline = malloc(bi.biWidth * sizeof(RGBTRIPLE));
        int append = 0;
        // iterate of scanline's pixel.
        for (int width = 0; width < oldWidth; width++)
        {
            RGBTRIPLE triple;

            // read RGB triple from infile.
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // TODO: write RGB triple to the output file.
            for (int i = 0; i < factor; i++)
            {
                *(scanline + append) = triple;
                append++;
            }

        }

        for (int i = 0 ; i < factor; i++)
        {
            fwrite(scanline, sizeof(RGBTRIPLE), (size_t) bi.biWidth, outptr);
            // add new padding to the large image.
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }


        // skip over padding if any
        fseek(inptr, oldPadding, SEEK_CUR);
        free(scanline);
    }


    fread(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // read BITMAPINFOHEADER from infile.
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    printf("New   biWidth: %d\n", bi.biWidth);
    printf("New   biHeight: %d\n", bi.biHeight);
    printf("New   biSizeImage: %d\n", bi.biSizeImage);
    printf("New   bfSize: %d\n", bf.bfSize);
    printf("New   biSize: %d\n\n", bi.biSize);

    // closing input file.
    fclose(inptr);

    // close output file.
    fclose(outptr);

    // free memory of scanline
    //free(scanline);
    // success
    return 0;
}

