/**
* Implementation of several functions to manipulate BMP files.
*
* Completion time: 30 mins
*
* @author Anubrolu charishma, Ruben Acuna
* @version 1.0
*/


#include "Image.h"


Image* image_create(struct Pixel** pArr, int width, int height) {

    struct Image *img = (struct Image*)malloc(sizeof(struct Image));
    img->pArr = pArr;
    img->width = width;
    img->height = height;

    return img;
}

void image_destroy(Image** img) {
    for(int i=0;i<image_get_height(*img);i++){
        free((*img)->pArr[i]);
    }
    free((*img)->pArr);
    free((*img));
}

struct Pixel** image_get_pixels(Image* img) {
    return img->pArr;
}

int image_get_width(Image* img) {
    return img->width;
}

int image_get_height(Image* img) {
    return img->height;
}

void image_apply_bw(Image* img) {
    for (int i = 0 ; i < img->height ; i++) {
        for (int j = 0 ; j < img->width ; j++) {
            unsigned char grayscale = (0.299*img->pArr[i][j].red) + (0.587*img->pArr[i][j].red) + (0.114*img->pArr[i][j].red);
            img->pArr[i][j].red = grayscale;
            img->pArr[i][j].green = grayscale;
            img->pArr[i][j].blue = grayscale;
        }
    }
}

void image_apply_colorshift(Image* img, int rShift, int gShift, int bShift) {
    for (int i = 0 ; i < img->height ; i++) {
        for (int j = 0 ; j < img->width ; j++) {
            img->pArr[i][j].red += rShift;
            img->pArr[i][j].green += gShift;
            img->pArr[i][j].blue += bShift;
        }
    }
}

void image_apply_resize(Image* img, float factor) {
    struct Pixel** newPixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * image_get_width(img) * factor);
    for (int p = 0; p < image_get_height(img) * factor; p++) {
        newPixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * image_get_width(img) * factor);
    }
    Image* newImg = image_create(newPixels, img->width*factor, img->height*factor);
    for (int i = 0 ; i < img->height*factor ; i++) {
        for (int j = 0 ; j < img->width*factor ; j++) {
            int nearestNeighbourI = ((i + 1)/factor) -1;
            int nearestNeighbourJ = ((j + 1)/factor) -1;
            newPixels[i][j].red = img->pArr[nearestNeighbourI][nearestNeighbourJ].red;
            newPixels[i][j].green = img->pArr[nearestNeighbourI][nearestNeighbourJ].green;
            newPixels[i][j].blue = img->pArr[nearestNeighbourI][nearestNeighbourJ].blue;
        }
    }

    img = newImg;
}


