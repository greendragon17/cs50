#include <stdio.h>
#include <cs50.h>

/*  Program: "Mario" v.1.0 - 10/18/2015
*   By: Darren Green - for CSx50 Fall 2015
*   Last update: 10/18/2015
*
*   The purpose of this program is to illustrate on the terminal window
*   a 2-D hemi-pyramid with user-defined height (between 0 and 23) using "#" characters
*   and spaces.  The pyramid's edge shall align horizontally on the right, shall have a
*   width of 2 "#" characters at the top level, and will reject all invalid input (anything
*   other than an integer between 0 and 23).
*/

int main(void)
{
    /** initialize var for pyramid height outside do-while loop 
    *   so it can be used thoughout application
    */
   
    int height;
    
    //  make sure that height is between 0 and 23 units    
   
     do
     {
        printf("height: ");
        height = GetInt();
     }
    while (height > 23 || height < 0);
   
   /** create numerical breakdown of how many HASHES
   *   are needed to build the BOTTOM layer the pyramid
   *   and how many SPACES are needed to build the TOP layer,
   *   based on the number of hashes
   */
        
   int hashes = height + 1;
   int spaces = hashes - 2;
   
    // now build the pyramid of size "height" from the top down
    
    for (int i = height; i > 0; i--)
    {     
        // print spaces before hashes for top (next) line
     
        for (int s = spaces; s > 0; s--)
        {   
            printf(" ");
        }
        
        // the next line will have 1 fewer space - update "spaces" variable for next line
        
        spaces--;
        
        // print hashes for top (next) line
        
        for (int h = hashes - spaces; h > 1; h--)
        {   
            printf("#");
        }
        
        // move to the next line of the pyramid
        
        printf("\n");
    }
}
