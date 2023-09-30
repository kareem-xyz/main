// Program reverses a wav audio file.
// Has some useful manipulations on reading and writing from files.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER *header);
int get_block_size(WAVHEADER *header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse.c inputfile.wav outputfile.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("ERROR: Something went wrong. Could not access input file.\n");
        return 1;
    }

    // Read header
    WAVHEADER *header = malloc(sizeof(WAVHEADER));
    if (header == NULL)
    {
        printf("ERROR: Something went wrong. Could Not copy into buffer.\n");
        return 1;
    }
    memset(header, 0, sizeof(WAVHEADER));
    fread(header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (check_format(header) != 0)
    {
        printf("ERORR: Unsupported file format.\n");
        return 1;
    }

    // Open output file for writing
    FILE *ouptr = fopen(argv[2], "w");
    if (ouptr == NULL)
    {
        printf("ERROR: Something went wrong. Could Not open output file.\n");
        return 1;
    }

    // Write header to file
    fwrite(header, sizeof(WAVHEADER), 1, ouptr);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file----
    // Get position of the starting sample block.
    // ftell is will give the offset just after the end of header.
    int start = ftell(inptr);

    // Go to the last block
    fseek(inptr, -block_size, SEEK_END);

    // A variable to store the offset after each copy and backwards seek.
    int current   = ftell(inptr);
    // A pointer to store the read block later on, and initialise it to 0s.
    void *block = malloc(block_size);
    if (block == NULL)
    {
        printf("ERORR: Something went wrong. Couldn't allocate memory for block transfering\n");
        return 1;
    }
    memset(block, 0, block_size);

    // loop through blocks until we have read them all.
    while (current >= start)
    {
        // Copy and paste the block.
        fread(block, block_size, 1, inptr);
        fwrite(block, block_size, 1, ouptr);

        // seek 2 blocks behind (to go to start of block before the one just read)
        fseek(inptr, - 2 * block_size, SEEK_CUR);

        //update the current offset value
        current = ftell(inptr);
    }
    // By end of loop all blocks should be copied in reverse.

    // Closing and freeing memory.
    fclose(inptr);
    fclose(ouptr);
    free(header);
    free(block);

    /*
    There is one part that I've not addressed, there seems to be another fucntion in c called
    calloc which should assign a memory and initalise it instead of using malloc and memset,
    however, I couldn't know how exactly to use it without arrays, so I ignored it. I might, however
    come back later on and update the code later on.
    */
}

int check_format(WAVHEADER *header)
{
    // check if WAVE code is available
    char wave[] = "WAVE";
    for (int i = 0; i < 4; i++)
    {
        if ((*header).format[i] != wave[i])
        {
            // return false
            return 1;
        }
    }
    // return true
    return 0;
}

int get_block_size(WAVHEADER *header)
{
    //Block size is the number of channels in an audio times the (((bytes))) per sample.
    int block_size = (*header).numChannels * (*header).bitsPerSample / 8;
    return block_size;
}