#include "filters.h"
#include "../Utils/Util.h"

// outputs filter 
double **b_filter(int filter_size){
    double ** filter = (double**) malloc (sizeof(double*)*filter_size);
    return filter;
}


// apply binomial filter to image
// iteration = number of time we apply the filter
pgm_file binomial_filter(pgm_file image, int filter_size, int iterations) {
    pgm_file output_image;
    // outputs correct binomial filter based on pascal triangle values 
    double ** filter = b_filter(filter_size);

    // depending on filter size, need to add padding to the image 
    pgm_file padding_img = malloc()
    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++) {

            // converting rgb to grayscale 
            int idx = i * image.cols + j;
        }
    }
    output_image = image;

    return output_image;
}

// apply median filter to image
pgm_file median_filter(pgm_file image, int filter_size, int iterations) {
    pgm_file output_image;

    printf("PLEASE IMPLEMENT median_filter\n");
    output_image = image;

    return output_image;
}