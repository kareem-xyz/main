// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool hasupper, haslower, hasdigit, hassymbol;
    //loop through word charcters
    for (int i = 0; i < strlen(password); i++)
    {
        if (isalpha(password[i]))
        {
            if (isupper(password[i]))
            {
                hasupper = true;
            }
            else
            {
                haslower = true;
            }

        }
        else if (isdigit(password[i]))
        {
            hasdigit = true;
        }
        else if (isblank(password[i]))
        {

        }
        else
        {
            hassymbol = true;
        }
    }
    if (hasupper && haslower && hasdigit && hassymbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
