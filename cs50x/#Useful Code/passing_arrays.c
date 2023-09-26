#include <string.h>
#include <cs50.h>
#include <stdio.h>

// we need to specify the size of the array when declaring a function it
void arrays(int image[2][3], int copy[2][3], int sizeof_image);
int main (void)
{
    int image[2][3] = { {0, 1, 2}, {3, 4, 5}};
    int copy[2][3];

    // when passing an array we only need the name
    arrays(image, copy, sizeof(image));

    /*
    The below code works here but if we were to copy it into a function it wouldn't (sizeof() wouldn't return the desired value), because of how c passes arrays
    so, we pass the size of the arrays as a parameter as well.


    memcpy(copy, image, sizeof(image));
    for (int i = 0; i < 2; i ++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("integer no.%i%i in image = %i\n", i, j, image[i][j]);
            printf("integer no.%i%i in copy  = %i\n", i, j, copy[i][j]);
        }
    }
    */
}

void arrays(int image[2][3], int copy[2][3], int sizeof_image)
{
    //memcpy here is  taking the address of the first element 
    memcpy(copy, image, sizeof_image);
    for (int i = 0; i < 2; i ++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("integer no.%i%i in image = %i\n", i, j, image[i][j]);
            printf("integer no.%i%i in copy  = %i\n", i, j, copy[i][j]);
        }
    }
}
