/*  CS50 pset2 - "Vigenere" v.1.0
*   By: Darren Green - last update 11/7/2015
*
*   This program takes one argument, an alphabetical string, which it uses as a key value to encrypt
*   a user-input string using Vigenere's cipher. 
* 
*   Vigenere's cipher uses a keyword to encrypt each character in the user-input string, sequentially
*   and cyclically.
*
*   The program must preserve the case in the outputted string, but ignores case in case of char value
*   (ex: A and a both equal 0).  Non-alphabetical characters are not encrypted, and the alphabetical character
*   following a non-alpha must use the next keyword char sequence (completely skip non-alpha chars).
*/

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //  User input must be a string containing ONLY alphabetical chars
    
    if(argc != 2)
    {
        printf("Usage: ./vigenere <keyword>\n");
        return 1;
    }

    //  Pass the value of user-input string from command line argument into string within program
    
    string keyword = argv[1];
    
    /*  Iterate over all chars in the keyword string to ensure that all are alpha, exit with code 1 if any
    *   non-alpha chars are present
    */
    
    int keyword_length = strlen(keyword);
    
    for(int i = 0; i < keyword_length; i++)
    {
        if(!isalpha(keyword[i]))
        {
            printf("Keyword must only contain letters A-Z and a-z\n");
            return 1;
        }        
    }
    
    //  Get user input for text to encipher, and store as a string; as well as int for message char length
    
    string message = GetString();
    int message_length = strlen(message);
    
    /*  This next subroutine has several important tasks:
    *
    *   The subroutine will input into a new array called "key" a series of integer values which correspond
    *   to the character position shifts used to encipher the user-input string
    *   
    *   1)  Iterate over all values in 'key'
    *   2)  Convert all lowercase letters to uppercase (to aid in next step)
    *   3)  Convert all chars to an integer between 0 and 25, where A = 0
    */
    
    int *key = malloc(sizeof(int) * keyword_length);
    for (int i = 0; i < keyword_length; i++)
    {
        if(islower(keyword[i]))
        {
            key[i] = (toupper(keyword[i]) - 65);
        }
        else
        {
            key[i] = keyword[i] - 65;
        }
    }
    
    /*  Encipher the user's message using the key as follows:
    *
    *   1)  Iterate over each char in message, while iterating cyclically over each int in key
    *   2)  For each alpha char in message, shift position by key[j] positions; modulus of 26 and preserve case range
    *   3)  Store the enciphered characters in a new array to be output to the command line when complete
    */
    
    char *cipher = malloc(sizeof(char) * message_length);
    for(int i = 0, j = 0; i < message_length; i++)
    {
        //  For non-alphanumeric characters in message, do not encipher: store to cipher[i] to print unchanged
        
        if(!isalpha(message[i]))
        {
            cipher[i] = message[i];
        }
        else
        {
            /*  Preserve case of alpha chars in string while enciphering
            *   Increment j by 1 after each encipherment of an alpha char modulated to key length
            *   Note that key length == keyword_length; as former array derives from latter
            */
            
            if(isupper(message[i]))
            {
                cipher[i] = (((message[i] - 65) + key[j]) % 26);
                cipher[i] += 65;
                j = (j + 1) % keyword_length;
            }
            else
            {
                cipher[i] = (((message[i] - 97) + key[j]) % 26);
                cipher[i] += 97;
                j = (j + 1) % keyword_length;
            } 
        }
    }
    
    //  Deallocate memory from key, as this array is no longer needed
    
    free(key);
    
    //  Print the enciphered message to the screen
    
    for(int i = 0; i < message_length; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");
    
    //  Deallocate memory from cipher at end of program
    
    free(cipher);
    
    //  successful execution of program returns value of 0, per specification

    return 0;
}
