#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // a black color is 0x000000, white is 0xffffff
    // loop through all pixels, row by row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // since color is only black.
            if (image[i][j].rgbtBlue == 0x00)
            {
                // if black to purple
                // no need to change yellow its already zero.
                image[i][j].rgbtRed = 0x80;
                image[i][j].rgbtBlue = 0x80;
            }
        }

    }
}
