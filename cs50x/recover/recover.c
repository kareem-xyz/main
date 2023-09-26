/*
Program to recover *deleted* jpg images from FAT memory card.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Size of blocks as per the FAT format.
#define BLOCKSIZE 512
typedef uint8_t Byte;

int main(int argc, char *argv[])
{
    // Check for correct usage.
    if (argc != 2)
    {
        printf("ERORR: Usage: ./recover file.raw\n");
        return 1;
    }

    // Open memory card file
    FILE *cardptr = fopen(argv[1], "r");
    if (cardptr == NULL)
    {
        printf("ERORR: Could not open file\n");
        return 2;
    }

    // Declarations
    Byte block[BLOCKSIZE];
    memset(block, 0, sizeof(block));

    FILE *jpgptr;

    int block_count = 0;

    // Name of file
    char *nameptr = malloc(8);
    strcpy(nameptr, "000.jpg");
    if (nameptr == NULL)
    {
        printf("ERORR: Something went wrong.\n");
        return 3;
    }

    // FOR FIRST BLOCK OF FIRST JPG ONLY
    while (fread(block, 1, BLOCKSIZE, cardptr) == BLOCKSIZE)
    {
        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && ((block[3] & 0xf0) == 0xe0))
        {
            // Open File
            jpgptr = fopen(nameptr, "w");
            if (jpgptr == NULL)
            {
                printf("ERORR: Something went wrong.\n");
                return 4;
            }

            // Write block to file
            fwrite(block, BLOCKSIZE, 1, jpgptr);

            block_count++;
            break;
            /*The reason why I specifically wrote the first jpeg first block outside the main copying
            loop (found below), is to avoid always checking whether the read block is the first one.*/
        }
    }

    // (Starts at the second block of the first jpeg) Loop through file till EOF
    while (fread(block, 1, BLOCKSIZE, cardptr) == BLOCKSIZE)
    {
        // if new jpeg
        // The & operator (Called the "bitwise and") in the last argument Basically skips saying (block[3] == 0xe0 0r 0xe1 0r... 0xef)
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // Close last file
            fclose(jpgptr);

            // Create new jpg file
            sprintf(nameptr, "%03i.jpg", block_count);
            jpgptr = fopen(nameptr, "w");
            if (jpgptr == NULL)
            {
                printf("ERORR: Something went wrong.\n");
                return 5;
            }

            // Write block to file
            fwrite(block, BLOCKSIZE, 1, jpgptr);

            block_count++;
        }

        // If same jpg, continue writing
        else
        {
            fwrite(block, BLOCKSIZE, 1, jpgptr);
        }

    }

    // free memory
    fclose(jpgptr);
    fclose(cardptr);
    free(nameptr);
}