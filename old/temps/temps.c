// CAN USE SELECTION SORT (TRUE)
// CAN USE BUUBLE SORT (PENDING)
// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);
void sort_bubble(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;
    // Simple change to sort_cities to tun selection sort, both accomplish the mission tho.
    char type;
    do
    {
    type = get_char("B for Bubble sort, S for selection sort:");
    } while (type != 'b' && type != 'B' && type != 's' && type != 'S');
    if (type == 'b' || type == 'B')
    sort_bubble();
    else
    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order (using selection sort here)
void sort_cities(void)
{
    // Selection sort:
    // Loop through the variables (v) times.
    for (int i = 0; i < NUM_CITIES; i++)
    {
        // Initialising some variables that will help in copying and pasting data later, for now they are the starting value [i]
        avg_temp new = temps[i];
        int n = i;
        // If a new value is lower than the starting one, replace the temporary holding variable (new) with it, and record its index at (n).
        for (int j = i; j < NUM_CITIES; j++)
        {
            // To flip the sorting simply change the sign below to <.
            if (temps[j].temp > new.temp)
            {
                n = j;
                new = temps[n];

            }
        }
        temps[n] = temps[i];
        temps[i] = new;
        // Apparently there's also a swaping function for arrays that could make the code more elegant.

    }
}

void sort_bubble(void)
{
    int swaps;
    do
    {
        swaps = 0;
        for (int i = 0; i < NUM_CITIES - 1; i++)
        {
            avg_temp copy;
            if (temps[i].temp > temps[i+1].temp)
            {
                copy = temps[i];
                temps[i] = temps[i+1];
                temps[i+1] = copy;
                swaps++;
            }
        }
    }
    while (swaps != 0);
}
