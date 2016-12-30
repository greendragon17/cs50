/*  CS50 pset2 - "Initials" v.1.0.0
*   By: Darren Green - last update 11/1/2015
*
*   This program asks a user to input first and last name, then gets their
*   first and last initials, and prints them to the screen as upper case
*   chars, without any punctuation.
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//  function to capitalize a letter if it isn't already: made function to save space

char capitalize(char a);

int main(void)
{
    //  User inputs first and last name, and is stored to string
    //  No prompt, per staff implementation of UI
    
    string name = GetString();
    
    //  Print out the first initial and capitalize
    
    printf("%c", capitalize(name[0]));
    
    /*  Loop through entire string to discover other names (separated by spaces)
    *   Use 't' as Boolean terminator: 0 = false, 1 = true   
    *
    *   If there is another name: print the capitalized letter to the screen and loop again
    *   When the string is at the end (hits \0) stop the loop
    */
    
    for (int i = 0, t = 0; t < 1; i++)
    {
        if (name[i] == ' ')
        {
            //  if a space is detected, another name is present: print capital initial
            printf("%c", capitalize(name[i + 1]));
        }
        else
        {
            if ((name[i] != ' ') && (name[i] != '\0'))
            {
                //  not a space and not NULL: iterate again
            }
            else
            {   
                //  it must be NULL: terminate loop
                t += 1;
            }
        }
    }   
    
    //  Add carriage return at end of runtime
    
    printf("\n");
    
    //  deallocate memory from all strings
    free(name);
}

//  define function "capitalize()"

char capitalize(char a)
{
    if (!isupper(a))
    {
        a = toupper(a);
        return a;
    }
    else return a;
}
