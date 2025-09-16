#include "TP1_funcs.h"
#include <stdlib.h>
#include <assert.h>
#include "../Utils/Util.h"


// TODO: split the image into three channels
// from an RGB image outputs => An image with only Reds, one with only blues and one with only greens 
void split_channels(ppm_file image,
                    ppm_file *image_r, ppm_file *image_g, ppm_file *image_b) {
    // Initializes all 3 images to have same type a size as init img 
    image_r->magic_number = image.magic_number;
    image_g->magic_number = image.magic_number;
    image_b->magic_number = image.magic_number;

    image_r->cols = image.cols;
    image_g->cols = image.cols;
    image_b->cols = image.cols;

    image_r->rows = image.rows;
    image_g->rows = image.rows;
    image_b->rows = image.rows;

    image_r->maxval = image.maxval;
    image_g->maxval = image.maxval;
    image_b->maxval = image.maxval;

    // Loop through init img and initialize the rgb values

    /* Memory allocation  */
    image_b->pixmap = (pixel *) malloc (image.cols * image.rows * sizeof(pixel));
    assert(image_b->pixmap);
    image_r->pixmap = (pixel *) malloc (image.cols * image.rows * sizeof(pixel));
    assert(image_r->pixmap);
    image_g->pixmap = (pixel *) malloc (image.cols * image.rows * sizeof(pixel));
    assert(image_g->pixmap);

    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++) {

            // setting values of red img 
            image_r->pixmap[i * image.cols + j].red = image.pixmap[i * image.cols + j].red;
            image_r->pixmap[i * image.cols + j].green = 0;
            image_r->pixmap[i * image.cols + j].blue = 0;

            // setting values of blue img 
            image_g->pixmap[i * image.cols + j].red = 0;
            image_g->pixmap[i * image.cols + j].green = image.pixmap[i * image.cols + j].green;
            image_g->pixmap[i * image.cols + j].blue = 0;

            // setting values of green img 
            image_b->pixmap[i * image.cols + j].red = 0;
            image_b->pixmap[i * image.cols + j].green = 0;
            image_b->pixmap[i * image.cols + j].blue = image.pixmap[i * image.cols + j].blue;
            }
        }
}

// TODO: convert rgb to grayscale
void rgb_to_gray(ppm_file image, pgm_file *image_gray, float brightness){
    // Initializes all 3 images to have same type a size as init img 
    if (image.magic_number != '3' || image.magic_number != '6'){
        // perror("WRONG FILE TYPE");
    }
    if (image.magic_number == '3')
    {
        // ASCII file 
        image_gray->magic_number = '2';
    } else {
        // Binary file 
        image.magic_number = '5';
    }
    
    image_gray->magic_number = image.magic_number;
    image_gray->cols = image.cols;
    image_gray->rows = image.rows;
    image_gray->maxval = image.maxval;

    image_gray->graymap = (gray *) malloc (image.cols * image.rows * sizeof(gray));
    assert(image_gray->graymap);

    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++) {

            // converting rgb to grayscale 
            int idx = i * image.cols + j;
            int r = image.pixmap[idx].red;
            int g = image.pixmap[idx].green;
            int b = image.pixmap[idx].blue;

            float gray_value = (0.2126f * r + 0.7152f * g + 0.0722f * b) * brightness;

            // Clamp to [0, maxval]
            // if (gray_value < 0) gray_value = 0;
            // if (gray_value > image.maxval) gray_value = image.maxval;

            image_gray->graymap[idx] = (gray) gray_value;
        }
    }
}