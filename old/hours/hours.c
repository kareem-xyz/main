#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    //Keeps asking the user until he enter a or t upper or lowercase, after which they are capitalised.
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    int sum = 0;
    // Calculate the sum of all hours in the array
    for (int i = 0; i < weeks; i++)
    {
        sum += hours[i];
    }
    if (output == 'A')
    {
        // Return the average
        return (float)sum / weeks;
    }
    // Else returns the sum
    return sum;
}