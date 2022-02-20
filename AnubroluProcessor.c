/**
 * THIS IS NOT A BASE FILE.
 *
 * The following code is a minimal example showing how to apply a blue color shift to the ttt.bmp test file using
 * the functionality you will implement in BMPHandler.h and Image.h. It serves as an example of the syntax that
 * your implementation should support. This code will not function until you have completed all the functionality in the
 * header files.
 *
 *
 *
 * Completion time: 334 minutes
 *
 * @author Anubrolu Charishma, Ruben Acuna
 * @version 1.0
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "BMPHandler.h"
#include "Image.h"
#include <string.h>


void main() {

    struct BMP_Header BMP;
    struct DIB_Header DIB;
    char string[100];
    int i=0;
    char *args[100];
    float scaling_factor;
    char input[100],output[100];
    int rshift=0,gshift=0,bshift=0;
    char dest_in[200],dest_out[200];
    int bwflag=0,scflag=0;
    printf("Enter the command line argument");
    gets(string);
    char *token = strtok(string, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    strcpy(input,args[0]);
    for (int j = 1; j<i; j++) {
        if(strcmp(args[j],"-w")==0)
        {
            bwflag=1;
        }
        if(strcmp(args[j],"-r") == 0){
            rshift=atoi(args[j+1]);
        }
        if(strcmp(args[j],"-g") == 0)
        {
            gshift=atoi(args[j+1]);
        }
        if(strcmp(args[j],"-b")==0)
        {
            bshift=atoi(args[j+1]);
        }
        if(strcmp(args[j],"-s")==0)
        {
            scflag=1;
            scaling_factor=atof(args[j+1]);
        }
        if(strcmp(args[j],"-o")==0)
        {
            strcpy(output,args[j+1]);
        }

    }
    puts(input);
    if(strcmp(input,"test2.bmp")==0 || strcmp(input,"ttt.bmp")==0 || strcmp(input,"wb.bmp")==0) {
        strcpy(dest_in, "/Users/kalyanreddy/CLionProjects/assignment 3/");
        strcat(dest_in, input);
        FILE *file_input = fopen(dest_in, "rb");
        readBMPHeader(file_input, &BMP);
        readDIBHeader(file_input, &DIB);
        struct Pixel **pixels = (struct Pixel **) malloc(sizeof(struct Pixel *) * DIB.height);
        for (int p = 0; p < DIB.height; p++) {
            pixels[p] = (struct Pixel *) malloc(sizeof(struct Pixel) * DIB.width);
        }
        readPixelsBMP(file_input, pixels, DIB.width, DIB.height);
        fclose(file_input);

        Image *img = image_create(pixels, DIB.width, DIB.height);
        if(scflag==1)
            image_apply_resize(img, scaling_factor);
        if(bwflag==1)
            image_apply_bw(img);
        image_apply_colorshift(img, rshift, gshift, bshift);
        strcpy(dest_out, "/Users/kalyanreddy/CLionProjects/assignment 3/");
        strcat(dest_out, output);
        FILE *file_output = fopen(dest_out,
                                  "wb");
        writeBMPHeader(file_output, &BMP);
        writeDIBHeader(file_output, &DIB);
        writePixelsBMP(file_output, image_get_pixels(img), image_get_width(img), image_get_height(img));
        fclose(file_output);
    }
    else
    {
        printf("error in opening the file since it doesn't exist");
    }

}

