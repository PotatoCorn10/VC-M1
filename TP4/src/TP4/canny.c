#include <stdio.h>
#include "canny.h"


// TODO: perform the Non-maximum suppression of the magnitudes using the angle direction (4 discretizations)
magnitude_angle_image directed_non_maximum_suppression(magnitude_angle_image magnitude_angle) {

    magnitude_angle_image output_image;

    printf("PLEASE IMPLEMENT directed_non_maximum_suppression\n");
    output_image.rows = 0;
    output_image.cols = 0;

    return output_image;
}


// TODO: perform the hysteresis thresholding. Set edges to 255 and non-edges to 0 value.
pgm_file hysteresis_thresholding(magnitude_angle_image max_magnitude_angle, int high_threshold, int low_threshold) {
    pgm_file output_image;

    printf("PLEASE IMPLEMENT hysteresis_thresholding\n");
    output_image.rows = 0;
    output_image.cols = 0;

    return output_image;
}

