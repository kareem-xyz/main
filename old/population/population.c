#include <cs50.h>
#include <stdio.h>

int main(void)
{

    long s;
    long e;
    int n = 0;

    // TODO: Prompt for start size
    // TODO: Prompt for end size
    do
    {
        s = get_long("Start size: ");
    }
    while (s < 9);

    do
    {
        e = get_long("End size: ");
    }
    while (e < s);

    // TODO: Calculate number of years until we reach threshold
    while (e > s)
    {
        s = s + s / 3 - s / 4;
        n += 1;
    }
    
    // TODO: Print number of years
    printf("Years: %i\n", n);
    printf("%li", s);







}
