//Had some fun messing with pointers and getting input.
//Program prints contacts in CSV file.
// Can add new contacts, or delete all the past ones and start fresh.

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int contact_count = get_int("Number of Contacts:");
    FILE *file;
    //Playing around ---
    printf("Do you want to continue or Delete the file and open new? (c/n)\n");
    char q;
    scanf("%c", &q);
    if (q == 'c')
    {
        file = fopen("phonebook.csv", "a");
    }
    else if (q == 'n')
    {
        file = fopen("phonebook.csv", "w");
    }
    else {
        printf("Something went wrong. Exiting.");
        return 1;
    }

    // Open CSV file
    char *name = malloc(30);
    int *number = malloc(sizeof(int));
    for (int i = 0; i < contact_count; i++)
    {
    // Name and number are pointers.
    // Name cannot exceed 30 Characters.

    printf("Name %i: ", i + 1);
    // scan user's input for a string and save it where the pointer (name) points towards
    scanf("%s", name);

    printf("Number %i: ", i + 1);
    // scan users innput for an int....
    scanf("%i", number);

    // Print to file
    fprintf(file, "%s,%i\n", name, *number);
    }
    free(name);
    free(number);
    // Close file
    fclose(file);

}
