// Program to check whether a credit card number is valid or not.
// Supports Visa, Mastercard, and American Express only.

#include <cs50.h>
#include <stdio.h>

// Functions explained below main
bool codeAMEX(long i);
bool codeMASTERCARD(long i);

int main(void)
{
    // Asks for credit card number
    long num = get_long("Credit card number:\n");
    long length = 0;
    // EDIT: suggestion: could just say length = strlen(itoa(num))

    // Calculates length of number
    for (long i = num; i > 0; length++)
    {
        i /= 10;
    }

    // Check whether length is valid, if it is not one of the values below, it's invalid
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        //return 0 simply tells the program to stop here, C syntax
        return 0;
    }

    // Variables used to check for Lohn Cecksum rules
    long n = num;
    int last;
    int evenlast;
    int doubleeven;
    int sum1 = 0;
    int sum2 = 0;
    int total;
    do
    {
        // Sums up odd ranks from right to left
        last = n % 10;
        n /= 10;
        sum1 += last;


        // Sums up 2 * even ranks from right to left
        evenlast = n % 10;
        doubleeven = 2 * evenlast;
        n /= 10;

        // A loop for doubleeven > 10, because it is double of digits, not actual number
        do
        {
            sum2 += (doubleeven) % 10;
            doubleeven /= 10;
        }
        while (doubleeven > 0);

    }
    while (n > 0);


    // Add both sums, divide by 10 and check whether remainder = 0
    total = sum1 + sum2;
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Whether the first digit will be ranked odd or even depends on number of digits
    else if ((length == 13 && last == 4) || (length == 16 && evenlast == 4))
    {
        printf("VISA\n");
        return 0;
    }
    else if (length == 15 && codeAMEX(num))
    {
        return 0;
    }
    else if (length == 16 && codeMASTERCARD(num))
    {
        return 0;
    }
    printf("INVALID\n");
}

// Check First 2 Digits
bool codeAMEX(long i)
{
    // Suggestion: could use i /= pow(10, 13) instead of the loop
    while (i > 100)
    {
        i /= 10;
    }
    if ((i == 34 || i == 37))
    {
        printf("AMEX\n");
        return 1;
    }
    else
    {
        return 0;
    }

}

bool codeMASTERCARD(long i)
{
    while (i > 100)
    {
        i /= 10;
    }
    if (i >= 51 && i <= 55)
    {
        printf("MASTERCARD\n");
        return 1;
    }
    else
    {
        return 0;
    }
}