#include "helpers.h"
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Duplicate image for the same reasons stated in blue function.
    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(RGBTRIPLE) * height * width);

    // loop through each pixel in the image
    for (int i = 0; i < height;  i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialise sums as 0. (Because the edge algorithm doesn't take the pixel itself into account).
            int redgx   = 0;
            int redgy   = 0;
            int greengx = 0;
            int greengy = 0;
            int bluegx  = 0;
            int bluegy  = 0;
            int factor;

            // ---------------------------Compute Gy---------------------------
            // ---loop 2 rows---
            for (int r = i - 1; r < i + 2; r += 2)
            {
                // if pixel's row is beyond border skip current adding.
                if (r < 0 || r > height - 1)
                {
                    continue;
                }

                // ---loop 3 columns---
                for (int c = j - 1; c < j + 2; c++)
                {
                    // if pixel colm is beyond border skip it
                    if (c < 0 || c > width - 1)
                    {
                        continue;
                    }

                    //-----Specific Configurations for factors per subpixel-----
                    // Row above
                    if (r == i - 1)
                    {
                        factor = -1;
                    }
                    // Row below
                    else
                    {
                        factor = 1;
                    }
                    // adjacent middle
                    if (c == j)
                    {
                        factor *= 2;
                    }

                    //---------------------------------------------------------

                    // Adding values
                    redgy   += factor * copy[r][c].rgbtRed;
                    greengy += factor * copy[r][c].rgbtGreen;
                    bluegy  += factor * copy[r][c].rgbtBlue;
                }

            }
            //-----------------------------End of Gy-------------------------------

            //-----------------------------Computing Gx----------------------------
            // loop 2 columns
            for (int c = j - 1; c < j + 2; c += 2)
            {
                // if pixel's colm is beyond border skip.
                if (c < 0 || c > width - 1)
                {
                    continue;
                }

                // loop 3 rows
                for (int r = i - 1; r < i + 2; r++)
                {
                    // if pixel row is beyond border skip.
                    if (r < 0 || r > height - 1)
                    {
                        continue;
                    }

                    //-----Configurations for factors per subpixel-----
                    // colm to left
                    if (c == j - 1)
                    {
                        factor = -1;
                    }
                    // colm to right
                    else
                    {
                        factor = 1;
                    }
                    // if middle in colmun
                    if (r == i)
                    {
                        factor *= 2;
                    }
                    //---------------------------------------------------------

                    // Adding Gx Values
                    redgx   += factor * copy[r][c].rgbtRed;
                    greengx += factor * copy[r][c].rgbtGreen;
                    bluegx  += factor * copy[r][c].rgbtBlue;
                }
            }
            //-----------------------------End of Gx---------------------------------

            // Final Values for the colors
            int red = round(sqrt(pow(redgy, 2)   + pow(redgx, 2)));
            int green = round(sqrt(pow(greengy, 2) + pow(greengx, 2)));
            int blue = round(sqrt(pow(bluegy, 2)  + pow(bluegx, 2)));

            // Final Check for Colors beyond 8-bit.
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // Changing the Picture
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;

        }
    }

    return;
}