/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// define a BYTE for convenience
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // open the RAW file
    FILE* file = fopen("card.raw", "r");

    if (file == NULL)
    {
        printf("Could not open the file...\n");
        return 1;
    }

    // I learned this from CS50 StackExchange; initialize 512 byte buffer
    BYTE buffer[512];

    // initialize filenum and current file
    int filenum = 0;
    FILE* currentfile = NULL;

    // here we go!
    // while the next buffer exists, keep on going
    while (fread(&buffer, 512 * sizeof(BYTE), 1, file) == 1)
    {
        // if the current buffer has the first 4 bytes of a header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // check if old file is still open
            if (currentfile != NULL)
            {
                fclose(currentfile);
            }

            // filename
            char* filename = malloc(8 * sizeof(BYTE));
            sprintf(filename, "%0.3d.jpg", filenum);

            // open the file
            currentfile = fopen(filename, "w");

            // thanks valgrind!
            free(filename);

            // error check
            if (currentfile == NULL)
            {
                printf("Could not create the file...\n");
                return 2;
            }

            // next!
            filenum++;
        }

        if (currentfile != NULL)
        {
            fwrite(&buffer, 512 * sizeof(BYTE), 1, currentfile);
        }
    }

    // close file
    fclose(file);
}
