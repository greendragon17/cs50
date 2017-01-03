/**
 * resize.c
 *
 * by - Darren Green - last update 11/7/2016
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes an uncompressed 24-bit BMP by a factor of n
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char* argv[]){
    // ensure proper usage
    if (argc != 4) {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    //  ensure factor of resize is an int between 0 and 100
    int n = atoi(argv[1]);
    
    if (n > 100 || n < 1) {
        printf("Resize factor must be positive int between 2 and 100\n");
        return 2;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
     //  make the new header for the new file
        // Make outfile BITMAPINFOHEADER
        BITMAPFILEHEADER bf_out;
        BITMAPINFOHEADER bi_out;
        
        // set outfile BITMAPFILEHEADER and BITMAPINFOHEADER equal to inputs
        bf_out = bf;
        bi_out = bi;
        
        // resize output BITMAPINFOHEADER height and width by n
        bi_out.biWidth = bi.biWidth * n;
        bi_out.biHeight = bi.biHeight * n;

        // determine padding for scanlines
        int padding_in =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        int padding_out = (4 - bi_out.biWidth * sizeof(RGBTRIPLE) % 4) % 4;
        
        //  Specify the size of the new file in bfSize
        bi_out.biSizeImage = abs(bi_out.biHeight) * bi_out.biWidth * 3 + abs(bi_out.biHeight) * padding_out;
        bf_out.bfSize = bi_out.biSizeImage + 54;

        // write outfile's BITMAPFILEHEADER
        fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Resize the image

    // determine number of height iterations
    int scans = abs(bi.biHeight);

    // iterate over infile's scanlines n times for height
    for (int i = 0; i < scans;  i++) {
        
        //  Write lines to outfile
        for (int j = 0; j < n; j++) {
            
            // iterate over infile's scanlines n times for width
            for (int width = 0; width < bi.biWidth; width++) {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                //  write the read bit n times
                for (int width1 = 0; width1 < n; width1++) {        
                    // write RGB triple to outfile and scale image
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                // skip padding in infile
                fseek(inptr, padding_in, SEEK_CUR);
                
                // add padding to outfile
                for (int k = 0; k < padding_out; k++){
                    fputc(0x00, outptr);
                }
                fseek(inptr, -(bi.biWidth * 3 + padding_in), SEEK_CUR);
            }

            //  rewind to the beginning of the width scanline
            fseek(inptr, bi.biWidth * 3 + padding_in, SEEK_CUR);
        }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
