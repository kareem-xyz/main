// Finds all prime numbers in a given range
// Efficient and fast


#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // Removes 1 and all even numbers from consideration
    // The number 2 is false for all loops and therefore is returned as true
    if (number == 1 || ((number % 2 == 0) && (number != 2)))
    {
        return false;
    }
    // j is 3 here because we are only checking odd numbers, and so is the increment
    int j = 3;
    for (j = 3; number > j; j += 2)
    {
        // Checks whether number is divisible
        if (number % j == 0)
        {
            return false;
        }

    } //jdjdj
    return true;
}
