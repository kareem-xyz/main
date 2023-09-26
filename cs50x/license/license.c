//VERY VERY annoying program to wrap your head around, reads a file of string plate numbers and prints it out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args.
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create temporary buffer to read into.
    char buffer[7];

    // Create array to store address of plate numbers strings.
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'.
        buffer[6] = '\0';

        // allocate memory for the currently read string.
        char *storeword = malloc(7 * sizeof(char));
        if (storeword == NULL)
        {
            printf("ERORR: Something went wrong.\n");
            return 1;
        }
        // copy from temporary buffer to the memory allocated.
        strncpy(storeword, buffer, 7);

        // Save address of plate number string in array.
        plates[idx] = storeword;
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        // print the plate number.
        printf("%s\n", plates[i]);
        // free up the space used by the string just printed.
        free(plates[i]);
    }
    // close the file.
    fclose(infile);
}
