#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    //--------CODE FOR LOOP METHOD-----
    //int number = 0;
    // Loops through each character starting from the last one (strlen-1), reads the character, turns it into its number (by subtracting 48), and adds that value to the sum.
    //for (int i = strlen(input), x = 1; i > 0; i--, x *= 10)
    //{
    //    number += (input[i - 1] - '0') * x;
    //}
    //return number;
    //--------------------------

    //-------CODE FOR RECURSIVE METHOD---
    // How many characters in the string.
    int length = strlen(input);
    // Base case: if index 0 is nul, that is the string is out of characters. ("strlen" ignores the null character in a string)
    if (length == 0)
    {
        return length;
    }
    else
    {
        // c is value of actual number (ASCII)
        int c = input[length - 1] - '0';
        // sets the last index (length-1) to nul
        input[length - 1] = '\0';
        // works from the bottom up (multiplying by 10 each time)
        // for example 123 starts with 3 then 2 then 1 then 0, returns 0 first, the 1, then 2 + 10, then 3 +12 * 10
        return c + 10 * convert(input);
    }
}