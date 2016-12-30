/*  CS50 pset2 - "Caesar" v.1.0
*   By: Darren Green - last update 11/7/2015
*
*   This program takes one argument, an integer, which it uses as a key value to encrypt
*   a user-input string using Caesar's cipher, shifted to the key'th position.  It preserves
*   the case of alphabetical characters, and it does not change non-alphabetical characters.
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //  user input MUST be a signle, non-negative integer; else exit and return code of "1" per problem spec
    
    if(argc != 2)
    {
        printf("Usage: ./caesar <key>\n");
        return 1;
    }
    
    //  store a value of the cypher key and verify that it is a non-negative int

    int key = atoi(argv[1]);
    
    if (key < 0)
    {
        printf("Key must be a non-negative integer.\n");
        return 1;
    }
  
    //  Get plaintext from user input and store it as a string, and get the length of the string
    
    string message = GetString();
    int message_length = strlen(message);

    /*  Take message and import each char, sequentially, into a new array where each char
    *   is encyphered by key number of spaces, preserving case and ignoring non-alphabetical chars.
    */
    
    int *cypher = malloc(sizeof(int) * message_length);
    for(int i = 0; i < message_length; i++)
    {
        //  check if each character is alphabetical - if not it won't be cyphered
        
        if(!isalpha(message[i]))
        {
            cypher[i] = message[i];
        }
        
        else
        {
            /*  Process encryption as follows:
            *   1)  Check if alpha chars are upper or lower, and process separately
            *   2)  Zero the index of each alpha char: char - 65 for upper and char - 97 for lower
            *   3)  Add key value to char, constrain with modulus of 26 (for each char in alphabet)
            *   4)  Write the value to the i'th index of the array
            */
            
            if (isupper(message[i]))
            {
                cypher[i] = ((message[i] - 65) + key) % 26;            
                cypher[i] += 65;                       
            }
            else
            {                
                cypher[i] = ((message[i] - 97) + key) % 26;            
                cypher[i] += 97;                
            }                 
        }                
    }
    
    //  print out the encyphered string of chars to the terminal
    
    for(int i = 0; i < message_length; i++)
    {
        printf("%c", cypher[i]);       
    }
    printf("\n");    
        
    //  clear all arrays
    
    free(cypher);
    
    //  normal operation of program returns value of "0"
    
    return 0;
}
