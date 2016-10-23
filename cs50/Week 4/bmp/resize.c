/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a bitmap by a factor of n, where n is a natural number (but not zero).
 *
 * Usage: ./resize factor infile outfile
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
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

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    BITMAPINFOHEADER bi_new = bi;
    bi_new.biWidth *= factor;
    bi_new.biHeight *= factor;
    int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;;
    bi_new.biSizeImage = ((bi_new.biWidth) * sizeof(RGBTRIPLE) + (padding_new)) * abs(bi_new.biHeight);

    BITMAPFILEHEADER bf_new = bf;
    bf_new.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi_new.biSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        RGBTRIPLE triples[bi_new.biWidth];

        // iterate over pixels in scanline first time
        for (int j = 0; j < bi.biWidth; j++)
        {
            // storage
            RGBTRIPLE triple;

            // read current pixel into storage
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store it n times in the array
            for (int l = factor; l > 0; l--)
            {
                triples[factor + ((j * factor) - l)] = triple;
            }
        }

        // vertical
        for (int m = 0; m < factor; m++)
        {
            // pixels (one whole row)
            for (int n = 0; n < bi_new.biWidth; n++)
            {
                fwrite(&triples[n], sizeof(RGBTRIPLE), 1, outptr);
            }

            // padding
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
