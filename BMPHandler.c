/**
* Implementation of several functions to manipulate BMP files.
*
* Completion time: 35 mins
*
* @author Anubrolu Charishma, Ruben Acuna
* @version 1.0
*/

#include "BMPHandler.h"

void readBMPHeader (FILE* file, struct BMP_Header* header) {
    if (file != NULL) {
        //read in the bitmap bmp header
        fread(&header->signature, (sizeof(char)), 2, file);
        fread(&header->size, (sizeof  (int)), 1, file);
        fread(&header->reserved1, (sizeof (short)), 1, file);
        fread(&header->reserved2, (sizeof (short)), 1, file);
        fread(&header->offset_pixel_array, (sizeof (int)), 1, file);
        printf("Signature : %c%c\n",header->signature[0],header->signature[1]);
        printf("size : %d\n",header->size);
        printf("reserved1 : %d\n",header->reserved1);
        printf("reserved2 : %d\n",header->reserved2);
        printf("offset_pixel_array : %d\n",header->offset_pixel_array);
    } else {
        printf("We reached the error");
    }
}

void readDIBHeader (FILE* file, struct DIB_Header* header) {
    if (file != NULL) {
        //read in the bitmap bmp header
        fread(&header->size, (sizeof(int)), 1, file);
        fread(&header->width, (sizeof  (int)), 1, file);
        fread(&header->height, (sizeof (int)), 1, file);
        fread(&header->planes, (sizeof (short)), 1, file);
        fread(&header->bits_per_pixel, (sizeof  (short)), 1, file);
        fread(&header->compression, (sizeof (int)), 1, file);
        fread(&header->image_size, (sizeof (int)), 1, file);
        fread(&header->x_pixels_per_meter, (sizeof (int)), 1, file);
        fread(&header->y_pixels_per_meter, (sizeof (int)), 1, file);
        fread(&header->color_palette_size, (sizeof (int)), 1, file);
        fread(&header->important_color_count, (sizeof (int)), 1, file);
    } else {
        printf("Error in opening the file2.\n");
    }
}

void writeBMPHeader(FILE* file, struct BMP_Header* header) {
//    printf("in WriteBMPHeader\n");
    fwrite(&header->signature, (sizeof(char)), 2, file);
    fwrite(&header->size, (sizeof(int)), 1, file);
    fwrite(&header->reserved1, (sizeof(short)), 1, file);
    fwrite(&header->reserved2, (sizeof(short)), 1, file);
    fwrite(&header->offset_pixel_array, (sizeof (int)), 1, file);
}


void writeDIBHeader(FILE* file, struct DIB_Header* header) {
//    printf("in Write DIB handler\n");
    fwrite(&header->size, (sizeof(int)), 1, file);
    fwrite(&header->width, (sizeof  (int)), 1, file);
    fwrite(&header->height, (sizeof (int)), 1, file);
    fwrite(&header->planes, (sizeof (short)), 1, file);
    fwrite(&header->bits_per_pixel, (sizeof  (short)), 1, file);
    fwrite(&header->compression, (sizeof (int)), 1, file);
    fwrite(&header->image_size, (sizeof (int)), 1, file);
    fwrite(&header->x_pixels_per_meter, (sizeof (int)), 1, file);
    fwrite(&header->y_pixels_per_meter, (sizeof (int)), 1, file);
    fwrite(&header->color_palette_size, (sizeof (int)), 1, file);
    fwrite(&header->important_color_count, (sizeof (int)), 1, file);
}

void makeBMPHeader(struct BMP_Header *header, int width, int height) {
    header->signature[0] = 'B';
    header->signature[1] = 'M';
    header->size = ((width*3) + (width*3)%4 )* height + 54 ;
    header->reserved1 = 0;
    header->reserved2 = 0;
    header->offset_pixel_array = 54;
}

void makeDIBHeader(struct DIB_Header *header, int width, int height) {
    header->size = 40;
    header->width = width;
    header->height = height;
    header->planes = 1;
    header->bits_per_pixel = 24;
    header->compression = 0;
    header->image_size = width * height;
    header->x_pixels_per_meter = 3780;
    header-> y_pixels_per_meter = 3780;
    header->color_palette_size = 0;
    header->important_color_count = 0;
}

void readPixelsBMP (FILE* file, struct Pixel** pArr, int width, int height) {
    for (int i = 0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            unsigned char r, g, b;
            fread(&pArr[i][j].blue, sizeof(char), 1, file);
            fread(&pArr[i][j].green, sizeof(char), 1, file);
            fread(&pArr[i][j].red, sizeof(char), 1, file);
//            printf("%d %d %d \n", pArr[i][j].blue, pArr[i][j].green, pArr[i][j].red);
        }
        fseek(file, sizeof(unsigned char) * (width*3)%4, SEEK_CUR);
    }
}

void writePixelsBMP (FILE* file, struct Pixel** pArr, int width, int height) {
    for (int i = 0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            unsigned char r, g, b;
            fwrite(&pArr[i][j].blue, sizeof(char), 1, file);
            fwrite(&pArr[i][j].green, sizeof(char), 1, file);
            fwrite(&pArr[i][j].red, sizeof(char), 1, file);
        }

        unsigned char* pad = malloc(sizeof(unsigned char) * ((width*3)%4));
        fwrite(pad, sizeof(unsigned char), (width*3)%4, file);
    }
}