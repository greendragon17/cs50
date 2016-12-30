/*  CS50 Problem Set "Hacker 1" - "credit" v.0.4.0
*
*   By: Darren Green -- Last update 10/26/2015
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    //  ask user to input credit card number, then store as long long
    
    printf("Number: ");
    
    long long ccn = GetLongLong(); 

    //  filter out negative numbers and zeros immediately, as they are all invalid
    
    if (ccn > 0)
    {
 
        /*  determine the length of the credit card number
        *   declare variable for digit length and initialize to 1
        *   initialize to 1 since all valid input contains at least one numerical digit
        */    
    
        int length = 1;
        long long length_loop = ccn;

        /*  length is determined by looping the credit card number through a series of
        *   divide-by-10 to determine how many "decimal places" there are
        *   the actual value of long long credit card number must be preserved long enough
        *   to be put into an array for processing, ergo another variable must be used for the
        *   while loop.  For loop is not used since the loop is not run on an explicit increment
        *   scheme - repeated iterations are dependent upon the value being able to be divided by 10
        */

        while (length_loop >= 10)
        {
            length_loop = length_loop / 10;
            length++;
        }       
        
        //  determine half length (without rounding) to assist in memory allocation
        
        int half = 0;
        
        if (((length / 2) % 2) != 0)
        {
            //  if above is true, half length is even
            half += (length / 2);
        }
        else
        {
            //  if it is odd, it will always round down, therefore add one
            half += (length / 2) + 1;
        }
            
        //  Perform the checksum step-wise:
        
        /*  Make an array "step_1" to take every digit and load it into an
        *   array, using powers of 10 division and modulus
        */
        
        int *digits_r = malloc(sizeof(int) * length);
        for (int i = 0; i < length; i++, ccn /= 10)
        {
            digits_r[i] = ccn % 10;
        }
        
        //  Make an array to reverse the digits stored in the previous array so that they read left to right
        
        int *digits = malloc(sizeof(int) * length);
        for (int i = length, n = 0; i > 0; i--, n++)
        {
            digits[i - 1] += digits_r[n];
        }               
        
        //  Deallocate from memory the array containing digits in reversed order
        
        free(digits_r);
        
        //   Process the data as follows:
        
        /*   Step 1: A. Starting with the penultimate digit, and include each other digit backwards
        *            B. Multiply each of these digits by two.  Will have to load into array
        *            C. Add the DIGITS of each number together, and store to memory as an int
        */ 
        
        int *step_1 = malloc(sizeof(int) * half);
        for (int i = (length - 2), n = 0; i < 0; i -= 2, n++)
        {
            step_1[n] += (digits[i] * 2);
        }
            
        //  now take the DOUBLED digits and add the DIGITS together for the next part
        
        int step_1_sum = 0;
        for (int i = 0; i < (half); i++)
        {
            if (step_1[i] >= 10)
            {
                //  handle double-digit DOUBLED digits (to add the DIGITS themselves together)
                //  this requires another sub-array to be used temporarily
                
                int *step_1_ddig = malloc(64);
                for (int n = 0; n < 2; n++, step_1[i] /= 10)
                {
                    step_1_ddig[n] = step_1[i] % 10;
                }
                
                //  add both digits of the DOUBLED digit to the step 1 sum
                
                step_1_sum += (step_1_ddig[0] + step_1_ddig[1]);
                
                //  deallocate sub-array
                
                free(step_1_ddig);
            }
            else
            {
                // for single-digit doubled digits, just add them to the step 1 sum
                
                step_1_sum += step_1[i];
            }
        }
        
        //  deallocate step_1 - no longer needed once sums are obtained
        
        free(step_1);
        
        /*   Step 2: Then, for every other digit from the penultimate digit, do the same and add it
        *            to the running tally
        */
        
        for (int i = (length - 1); i > 0; i -= 2)
        {
            step_1_sum += digits[i];
        }
     
        //  Now perform the actual checksum:
        
        int checksum = step_1_sum % 10;               
        
        //  Now categorize the number based on brand, and evaluate if it is valid
        
        //  Amex cards are 15 digits and start with 34 or 37
        
        if ((length == 15) && (digits[0] == 3) && ((digits[1] == 4) || (digits[1] == 7)) && (checksum == 0))
        {
            printf("AMEX\n");
            goto exit;
        }
        
        //  Mastercard is 16 digits and starts with 51, 52, 53, 54, or 55
        
        if ((length == 16) && (digits[0] == 5) && (digits[1] >= 1) && (digits[1] <= 5) && (checksum == 0))
        {    
            printf("MASTERCARD\n");
            goto exit;        
        }
        
        //  Visa is 13 or 16 digits and starts with 4
         
        if (((length == 13) || (length == 16)) && (digits[0] == 4) && (checksum == 0))
        {                            
            printf("VISA\n");
            goto exit;
        }
        
        //  Invalid Numbers are what remain
        
        else
        {
        printf("INVALID\n");
        }
    
        //  exit from the program when a valid credit card number is found    
 
        exit:    
    
        //  deallocate memory used for array
        
        
        free(digits);     
     }
     else
     {
        printf("INVALID\n");
     }      
}
