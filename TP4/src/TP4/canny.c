#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "canny.h"

#define DEG2RAD(x) ((x) * 3.14 / 180.0)

// Non-maximum suppression using gradient direction
magnitude_angle_image directed_non_maximum_suppression(magnitude_angle_image magnitude_angle) {
    magnitude_angle_image output;
    output.rows = magnitude_angle.rows;
    output.cols = magnitude_angle.cols;

    output.magnitude = (float*) malloc(magnitude_angle.rows * magnitude_angle.cols * sizeof(float));
    output.angle = (float*) malloc(magnitude_angle.rows * magnitude_angle.cols * sizeof(float));

    // Copy angles (they don’t change)
    for (int i = 0; i < magnitude_angle.rows * magnitude_angle.cols; i++)
        output.angle[i] = magnitude_angle.angle[i];

    // Process each pixel (skip borders)
    for (int y = 1; y < magnitude_angle.rows - 1; y++) {
        for (int x = 1; x < magnitude_angle.cols - 1; x++) {
            int idx = y * magnitude_angle.cols + x;
            float angle = magnitude_angle.angle[idx] * 180.0 / 3.14;
            if (angle < 0) angle += 180.0;

            float mag = magnitude_angle.magnitude[idx];
            float mag1 = 0.0, mag2 = 0.0;

            // Determine neighbors based on angle
            if ((angle >= 0 && angle < 22.5) || (angle >= 157.5 && angle <= 180))
            {
                mag1 = magnitude_angle.magnitude[y * magnitude_angle.cols + (x - 1)];
                mag2 = magnitude_angle.magnitude[y * magnitude_angle.cols + (x + 1)];
            }
            else if (angle >= 22.5 && angle < 67.5)
            {
                mag1 = magnitude_angle.magnitude[(y - 1) * magnitude_angle.cols + (x + 1)];
                mag2 = magnitude_angle.magnitude[(y + 1) * magnitude_angle.cols + (x - 1)];
            }
            else if (angle >= 67.5 && angle < 112.5)
            {
                mag1 = magnitude_angle.magnitude[(y - 1) * magnitude_angle.cols + x];
                mag2 = magnitude_angle.magnitude[(y + 1) * magnitude_angle.cols + x];
            }
            else if (angle >= 112.5 && angle < 157.5)
            {
                mag1 = magnitude_angle.magnitude[(y - 1) * magnitude_angle.cols + (x - 1)];
                mag2 = magnitude_angle.magnitude[(y + 1) * magnitude_angle.cols + (x + 1)];
            }

            // Keep only local maxima
            if (mag >= mag1 && mag >= mag2)
                output.magnitude[idx] = mag;
            else
                output.magnitude[idx] = 0.0f;
        }
    }

    return output;
}


// Hysteresis thresholding with edge tracking
pgm_file hysteresis_thresholding(magnitude_angle_image max_magnitude_angle, int high_threshold, int low_threshold) {
    pgm_file output;
    output.rows = max_magnitude_angle.rows;
    output.cols = max_magnitude_angle.cols;
    int total = output.rows * output.cols;

    output.graymap = (unsigned char*) malloc(total * sizeof(unsigned char));

    // Step 1: classify pixels
    unsigned char *strong = malloc(total);
    unsigned char *weak = malloc(total);

    for (int i = 0; i < total; i++) {
        float val = max_magnitude_angle.magnitude[i];
        if (val >= high_threshold) {
            output.graymap[i] = 255;
            strong[i] = 1;
            weak[i] = 0;
        } else if (val >= low_threshold) {
            output.graymap[i] = 128; // mark as weak
            weak[i] = 1;
            strong[i] = 0;
        } else {
            output.graymap[i] = 0;
            weak[i] = strong[i] = 0;
        }
    }

    // Step 2: promote weak edges connected to strong ones
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int y = 1; y < output.rows - 1; y++) {
            for (int x = 1; x < output.cols - 1; x++) {
                int idx = y * output.cols + x;
                if (weak[idx] && output.graymap[idx] != 255) {
                    // check 8 neighbors
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            int nidx = (y + dy) * output.cols + (x + dx);
                            if (strong[nidx]) {
                                output.graymap[idx] = 255;
                                strong[idx] = 1;
                                weak[idx] = 0;
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    // Step 3: remove remaining weak edges
    for (int i = 0; i < total; i++) {
        if (output.graymap[i] != 255)
            output.graymap[i] = 0;
    }

    free(strong);
    free(weak);

    output.maxval = 255;
    return output;
}
