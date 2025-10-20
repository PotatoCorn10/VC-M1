#include <stdio.h>
#include "gradients.h"
#include "../Utils/filters.h"
#include <math.h>

// TODO: compute the gradients of the input image
gradient_image compute_gradients(pgm_file image) {

    gradient_image output_image;
    output_image.cols = image.cols;
    output_image.rows = image.rows;

    output_image.derivative_x = (derivative*) malloc (image.cols*image.rows*(sizeof(derivative)));
    output_image.derivative_y = (derivative*) malloc (image.cols*image.rows*(sizeof(derivative)));

    pgm_file padded = add_padding(image, 3);

    for (int y = 1; y < image.rows; y++) {
        for (int x = 1; x < image.cols; x++) {
            int idx = y * image.cols + x;
            output_image.derivative_x[y * image.cols + x] = (derivative) padded.graymap[y * image.cols + (x + 1)] - (derivative) padded.graymap[y * image.cols + (x - 1)]; // Gx = P_right - P_left
            output_image.derivative_y[y * image.cols + x] = (derivative) padded.graymap[(y + 1) * image.cols + x] - (derivative) padded.graymap[(y - 1) * image.cols + x]; // Gy = P_bottom - P_top
        }
    }
    return output_image;
}

float square(float a) {
    return a*a;
}

// TODO: compute the magnitude and angle of the gradients
magnitude_angle_image compute_magnitude_angle(gradient_image gradients){
    magnitude_angle_image output_image;

    output_image.rows = gradients.rows;
    output_image.cols = gradients.cols;

    output_image.magnitude = (float*) malloc (gradients.cols*gradients.rows*sizeof(float));
    output_image.angle = (float*) malloc (gradients.cols*gradients.rows*sizeof(float));
    
    for (int y = 0; y < gradients.rows; y++) {
        for (int x = 0; x < gradients.cols; x++) {
            int idx = y * gradients.cols + x;
            output_image.magnitude[y * gradients.cols + x] = (float)sqrt((double)(square(gradients.derivative_x[y * gradients.cols + x]) + square(gradients.derivative_y[y * gradients.cols + x])));
            output_image.angle[y * gradients.cols + x] = atan2(gradients.derivative_y[y * gradients.cols + x],gradients.derivative_x[y * gradients.cols + x]);
        }
    }

    return output_image;
}


// TODO: map gradients into an image that can be viewed [0,255]
// Be careful, note that values can be negative and larger than 255.
// Usually a mapping is performed where the 0 magnitude is mapped to the intensity 127 (255\/2).
pgm_file map_gradients_magnitude(magnitude_angle_image magnitude) {
    pgm_file output_image;

    output_image.rows = magnitude.rows;
    output_image.cols = magnitude.cols;

    for (int y = 1; y < magnitude.rows; y++) {
        for (int x = 1; x < magnitude.cols; x++) {
            int idx = y * magnitude.cols + x;
            output_image.magnitude[y * gradients.cols + x] = (float)sqrt((double)(square(gradients.derivative_x[y * gradients.cols + x]) + square(gradients.derivative_y[y * gradients.cols + x])));
            output_image.angle[y * gradients.cols + x] = atan2(gradients.derivative_y[y * gradients.cols + x],gradients.derivative_x[y * gradients.cols + x]);
        }
    }
    
    return output_image;
}