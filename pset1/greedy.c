#include <stdio.h>
#include <cs50.h>
#include <math.h>

/*  Program: "Greedy" v.1.0 - 10/18/2015
*   By: Darren Green - for CSx50 Fall 2015
*   Last update: 10/18/2015
*
*   The purpose of this program is to establish the fewest possible number of
*   coins needed to give correct change for a user-input dollar amount, while
*   rejecting invalid user input (anything other than positive floating point numbers),
*   and only using coins with denominations of $0.25, $0.10, $0.05, and $0.01.
*/

int main(void)
{
    /*  set a variable to track dollar amount then round it into cents
    *   as well as a variable to track the number of coins needed to give
    *   correct change
    */
    
    float dollars;
    int cents;
    int coins = 0;
    
    /* set up loop that prompts users to input money amount 
    *  but only allows positive values
    */
    
    do
    {
        printf("O hai! How much change is owed?\n");
        dollars = GetFloat();
    }
    while (dollars < 0);
    
    // convert floating value of dollars into int value for cents using round
    
    cents = round((dollars * 100));
    
    /*  begin algorithm to establish the minimum number of coins needed to return change
    *   for the user-input dollar amount.  The algorithm shall function as a top-down (largest
    *   available denomination) filter and return an integer value to the user equal to the total
    *   number of coins needed, irrespective of denomination.
    *
    *   The algorithm works by subtracting the maximum number of each coin in descending order of
    *   denomination from a running total of the user input dollar value (as cents), adding 1 to the
    *   total number of coins with each subtraction.
    */
    
    // checks to see how many quarters can be used, if any
    
    if (cents >= 25)
    {
        while (cents >= 25)
        {
            cents = cents - 25;
            coins++;
        }
    }
    
    // checks to see how many dimes can be used, if any
    
    if (cents >= 10)
    {
        while (cents >= 10)
        {
            cents = cents - 10;
            coins++;
        }
    }
    
    // checks to see how many nickels can be used, if any
    
    if (cents >= 5)
    {
        while (cents >= 5)
        {
            cents = cents - 5;
            coins++;
        }
    }
    
    // checks to see how many pennies should be used, after all higher
    // denominations have been used
    
    if (cents >= 1)
    {
        while (cents >= 1)
        {
            cents = cents - 1;
            coins++;
        }
    }
    
    // returns the total number of coins to the user
    
    printf("%i\n", coins);
}
