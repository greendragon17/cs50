/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    //  If the user fails to input between one and two parameters, prompt user to retry
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    //  Converts the first user input string (parameter 1) into an array of integers using atoi()
    int n = atoi(argv[1]);

    /****************************************************************************************************************************
    *   If the user inputs a "seed value" (second argument), generate a pseudorandom long int using the user-input seed value as a seed 
    *   for the srand() function, and convert it to an array of ints using the atoi() function
    *   
    *   Else generate a psuedorandom long int using the time in seconds since the Epoch as the seed value, and convert it to an array
    *   of ints using the atoi() function
    *
    ******************************************************************************************************************************/
    
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    //  Print to the screen n number of randomly generated numbers: obtained by multiplying a pseudorandomly generated number
    //  multiplied by LIMIT (a constant defined at the start of the code), and casting it as an int
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
