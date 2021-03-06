/**
 * recover.c
 *
 * by: Darren Green
 * Last Revision 1/9/2017
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

int main(int argc, char* argv[]){
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
        free(filename);
        return 2;
    }
    
    // make pointer for outfile
    FILE* outfile;
    
    // buffer to read memory card and check signature
    unsigned char buffer[512] = {0};

    // check - if file open == 1
    int open = 0;
    
    // REPEAT UNTIL END OF CARD
    // read data into buffer from memory card 1-byte 512x times until EOF
    while(fread(buffer, 1, 512, card) > 0){
        // START OF A JPG?
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe1 || buffer[3] == 0xe0)){
            // IF new file is needed, ELSE file is already open
            if(open == 0){
                // make the outfile
                sprintf(filename, "%03i.jpg", counter);
            
                outfile = fopen(filename, "w");
                if(outfile == NULL){
                    printf("Could not create new JPG file.  Exiting...\n");
                    fclose(card);
                    free(filename);
                    return 3;
                }
                
                // mark file as open
                open++;
            }
            else{
                // close the open file
                fclose(outfile);
                counter++;
                    
                // make a new file to continue
                sprintf(filename, "%003i.jpg", counter);
                outfile = fopen(filename, "w");
                if(outfile == NULL){
                    printf("Could not create new JPG file.  Exiting...\n");
                    fclose(card);
                    free(filename);
                    return 4;
                }
            }
        }
        
        // ALREADY FOUND A JPG?
        if(open == 1){
            //  write block to outfile
            if(fwrite(buffer, 1, 512, outfile) < 512){
                // CLOSE ANY REMAINING FILES
                fclose(card);
                free(filename);
                return 0;
                }
            }
        }
    }
