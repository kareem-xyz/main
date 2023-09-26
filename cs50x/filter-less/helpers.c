#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each pixel
    {
        for (int j = 0; j < width; j++)
        {
            // pointer to colors to make things easier
            BYTE *red = &image[i][j].rgbtRed;
            BYTE *green = &image[i][j].rgbtGreen;
            BYTE *blue = &image[i][j].rgbtBlue;

            // Caculate the grayscale
            int sum = (*red) + (*green) + (*blue) ;
            int gray = round(sum / 3.0);

            // Set pixel to grayscale
            *red = gray;
            *green = gray;
            *blue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each pixel
    for (int i = 0; i < height;  i++)
    {
        for (int j = 0; j < width; j++)
        {
            // pointer to colors to make things easier
            BYTE *red = &image[i][j].rgbtRed;
            BYTE *green = &image[i][j].rgbtGreen;
            BYTE *blue = &image[i][j].rgbtBlue;

            // Caculate the new sepia colors in integers.
            int sepiaRed = round(.393 * (*red) + .769 * (*green) + .189 * (*blue));
            int sepiaGreen = round(.349 * (*red) + .686 * (*green) + .168 * (*blue));
            int sepiaBlue = round(.272 * (*red) + .534 * (*green) + .131 * (*blue));

            //Check for crossing limits
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set pixel to new sepia colors
            *red = sepiaRed;
            *green = sepiaGreen;
            *blue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height;  i++)
    {
        // we dont need to read through all the pixels in a row since then we will do a double reflection, essentially returning the original photo.
        // if width is odd we need not reflect the middle pixel on itself
        // loop through left half of photo
        float k = width / 2.0;
        for (int j = 0; j < k; j++)
        {
            // pointer to colors of pixel 1
            BYTE *r1 = &image[i][j].rgbtRed;
            BYTE *g1 = &image[i][j].rgbtGreen;
            BYTE *b1 = &image[i][j].rgbtBlue;

            // pointers to colors of pixel 2 (the one we reflect onto)
            BYTE *r2 = &image[i][width - 1 - j].rgbtRed;
            BYTE *g2 = &image[i][width - 1 - j].rgbtGreen;
            BYTE *b2 = &image[i][width - 1 - j].rgbtBlue;

            // Temporary variables for copying
            // copy 1 onto tmp.
            BYTE tmpR = *r1;
            BYTE tmpG = *g1;
            BYTE tmpB = *b1;

            // copy 2 onto 1.
            *r1 = *r2;
            *g1 = *g2;
            *b1 = *b2;

            // copy tmp (original 1) onto 2.
            *r2 = tmpR;
            *g2 = tmpG;
            *b2 = tmpB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy image used to not alter original photo when calculating blur values
    RGBTRIPLE copy[height][width];
    // I got confused while reading the documentation for how memcpy works, and how passing arrays into functions works as pointers when passing arrays by reference. I will probably update the code below after I mess with it in playground.
    // So I tried many times using memcpy until i found a varaiation that works.
    memcpy(copy, image, sizeof(RGBTRIPLE) * height * width);

    /* below is an alternative method that could be used to copy the array. (uses nested loops)


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    */


    // loop through each pixel
    for (int i = 0; i < height;  i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialise sums as the color of the pixel itself
            int redsum = copy[i][j].rgbtRed;
            int greensum = copy[i][j].rgbtGreen;
            int bluesum = copy[i][j].rgbtBlue;
            float pixel_count = 1.0;

            // loop to read nearby pixels from upper left pixel of current one
            for (int r = i  - 1; r <= i + 1; r++)
            {
                // if pixel's row is beyond border skip it.
                if (r < 0 || r > height - 1)
                {
                    continue;
                }

                for (int c = j - 1; c <= j + 1; c++)
                {
                    // if same pixel skip (already added)
                    // reason we don't initialise is because then we have to write other special conditionals for pixels on the borders
                    if (r == i && c == j)
                    {
                        continue;
                    }
                    // if pixel colm is beyond border skip it
                    if (c < 0 || c > width - 1)
                    {
                        continue;
                    }
                    redsum += copy[r][c].rgbtRed;
                    greensum += copy[r][c].rgbtGreen;
                    bluesum += copy[r][c].rgbtBlue;
                    pixel_count++;
                }
            }
            // adjust value for original using new blur values
            image[i][j].rgbtRed = round(redsum / pixel_count);
            image[i][j].rgbtGreen = round(greensum / pixel_count);
            image[i][j].rgbtBlue = round(bluesum / pixel_count);
        }
    }
    return;
}
