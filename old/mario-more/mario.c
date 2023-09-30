//Program to type 2 triangles of #

#include <cs50.h>
#include <stdio.h>

string print(int row);

int main(void)
{
    // Gets height of trianlges
    int h;
    do
    {
        h = get_int("Height?");
    }
    // Not sure why 8 is the maximum, but I tried up to 60 and it works fine, around 90 tho things get weird.
    while (h < 1 || h > 8);

    //Loops for Each Row
    for (int r = 1; r <= h; r++)
    {
        // Prints Spaces
        for (int i = h - r; i > 0; i--)
        {
            printf(" ");
        }

        // Prints #
        for (int j = 1; j <= r; j++)
        {
            printf("#");
        }

        //Prints Double Spaces column
            printf("  ");

        // Mirrors  Printing #
        for (int j = 1; j <= r; j++)
        {
            printf("#");
        }
        // Goes to next line
        printf("\n");
    }
}
    // Program isn't the most efficient. Could use a function for printing # instead of repeating.