/**
 * recover.c
 *
 * by: Darren Green
 * Last Revision 1/3/2016
 * 
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // ensure proper usage
    if(argc != 1){
        printf("Usage: ./recover\n");
        return 1;
    }
    
    // make counter for filename and filename
    int counter = 0;
    char* filename = malloc(sizeof(char) * 8);
    
    // open memory card file
    FILE* card = fopen("card.raw", "r");
    if(card == NULL){
        printf("Could not open card.raw\n");
        return 2;
    }
    
    // buffer to read memory card and check signature
    BYTE buffer[512];
    
    // read into buffer from memory card 1-byte 512x times
    while(fread(&buffer, 512, 1, card) == 512){
            
            // check for the start of a JPG
            if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe1){
                
                //keep going until EOF is reached
                
                // open a new JPG file
                sprintf(filename, "%03i.jpg", counter);
            
                FILE* pic = fopen(filename, "w");
                if(pic == NULL){
                    printf("Could not create new JPG file.  Exiting...\n");
                    fclose(card);
                    return 3;
                }
            
            // write to the outfile
            fwrite(pic, 512, 1, buffer);
            
            // close the outfile
            fclose(pic);
            }
    }
    
    // detect end of file
    
    // close any remaining files
    fclose(card);
    
    free(filename);
    
    return 0;
}
