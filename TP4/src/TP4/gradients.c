#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gradients.h"
#include "../Utils/filters.h"   // for add_padding

// Helper function for squaring
static inline float square(float a) { return a * a; }

// Compute gradients using Sharr filters
gradient_image compute_gradients(pgm_file image) {
    gradient_image output;
    output.rows = image.rows;
    output.cols = image.cols;

    output.derivative_x = (derivative*) malloc(image.rows * image.cols * sizeof(derivative));
    output.derivative_y = (derivative*) malloc(image.rows * image.cols * sizeof(derivative));

    // Sharr filter kernels
    int sharr_x[3][3] = {
        {  3,  0, -3 },
        { 10,  0, -10 },
        {  3,  0, -3 }
    };
    int sharr_y[3][3] = {
        {  3, 10,  3 },
        {  0,  0,  0 },
        { -3, -10, -3 }
    };

    pgm_file padded = add_padding(image, 3);

    for (int y = 1; y < image.rows + 1; y++) {
        for (int x = 1; x < image.cols + 1; x++) {
            double gx = 0.0, gy = 0.0;

            // Apply 3x3 convolution
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixel = padded.graymap[(y + ky) * padded.cols + (x + kx)];
                    gx += sharr_x[ky + 1][kx + 1] * pixel;
                    gy += sharr_y[ky + 1][kx + 1] * pixel;
                }
            }

            int idx = (y - 1) * image.cols + (x - 1);
            output.derivative_x[idx] = gx;
            output.derivative_y[idx] = gy;
        }
    }

    return output;
}


// Compute magnitude and orientation (angle) of gradients
magnitude_angle_image compute_magnitude_angle(gradient_image gradients) {
    magnitude_angle_image output;
    output.rows = gradients.rows;
    output.cols = gradients.cols;

    output.magnitude = (float*) malloc(gradients.rows * gradients.cols * sizeof(float));
    output.angle = (float*) malloc(gradients.rows * gradients.cols * sizeof(float));

    for (int y = 0; y < gradients.rows; y++) {
        for (int x = 0; x < gradients.cols; x++) {
            int idx = y * gradients.cols + x;
            float gx = gradients.derivative_x[idx];
            float gy = gradients.derivative_y[idx];

            output.magnitude[idx] = sqrt(square(gx) + square(gy));
            output.angle[idx] = atan2(gy, gx); // radians
        }
    }

    return output;
}


// Map gradient magnitudes into displayable image [0,255]
pgm_file map_gradients_magnitude(magnitude_angle_image magnitude) {
    pgm_file output;
    output.rows = magnitude.rows;
    output.cols = magnitude.cols;

    output.graymap = (unsigned char*) malloc(magnitude.rows * magnitude.cols * sizeof(unsigned char));

    // Find min and max values
    float min_val = magnitude.magnitude[0];
    float max_val = magnitude.magnitude[0];

    int total = magnitude.rows * magnitude.cols;
    for (int i = 1; i < total; i++) {
        if (magnitude.magnitude[i] < min_val) min_val = magnitude.magnitude[i];
        if (magnitude.magnitude[i] > max_val) max_val = magnitude.magnitude[i];
    }

    float range = max_val - min_val;
    if (range == 0) range = 1; // Avoid division by zero

    // Normalize magnitudes to [0,255]
    for (int i = 0; i < total; i++) {
        float norm = (magnitude.magnitude[i] - min_val) / range;
        output.graymap[i] = (unsigned char)(norm * 255.0f);
    }
    output.maxval = 255;
    return output;
}
