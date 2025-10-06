#include "filters.h"
#include "../Utils/Util.h"

// outputs filter 
// Function to compute binomial coefficient C(n, k)
unsigned long binomial_coeff(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    unsigned long res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// Function to generate a binomial filter matrix of given size
double** b_filter(int size) {
    if (size < 1) return NULL;

    // Allocate 2D array for the kernel
    double **kernel = malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        kernel[i] = malloc(size * sizeof(double));
    }

    // Generate 1D binomial coefficients (Pascal row)
    double *coeffs = malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        coeffs[i] = (double)binomial_coeff(size - 1, i);
    }

    // Compute the outer product to get the 2D filter
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            kernel[i][j] = coeffs[i] * coeffs[j];
            sum += kernel[i][j];
        }
    }

    // Normalize so the total sum = 1
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            kernel[i][j] /= sum;
        }
    }

    free(coeffs);
    return kernel;
}


// apply binomial filter to image
// iteration = number of time we apply the filter
pgm_file binomial_filter(pgm_file image, int filter_size, int iterations) {
    pgm_file output_image;
    // outputs correct binomial filter based on pascal triangle values 
    double ** filter = b_filter(filter_size);

    // depending on filter size, need to add padding to the image 
    int padding_size = filter_size / 2;
    pgm_file padding_img; padding_img.cols = image.cols + 2*padding_size; padding_img.rows = image.rows + 2*padding_size;
    padding_img.graymap = (gray*)malloc(sizeof(gray) * padding_img.rows * padding_img.cols);

    for (int i = 0; i < padding_img.rows; i++){
      for(int j = 0; j < padding_img.cols; j++){
        if(i < padding_size || i >= padding_img.rows - padding_size || j < padding_size || j >= padding_img.cols - padding_size){
          padding_img.graymap[i * padding_img.cols + j] = 0;
        } else {
          padding_img.graymap[i * padding_img.cols + j] = image.graymap[(i - padding_size) * padding_img.cols + (j - padding_size)];
        }
      }
    }

    
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