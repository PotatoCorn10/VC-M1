#ifndef CANNY_H
#define CANNY_H

#include "../Utils/types.h"

// TODO: perform the Non-maximum suppression of the magnitudes using the angle direction (4 discretizations)
magnitude_angle_image directed_non_maximum_suppression(magnitude_angle_image magnitude_angle);

// TODO: perform the hysteresis thresholding
pgm_file hysteresis_thresholding(magnitude_angle_image max_magnitude_angle, int high_threshold, int low_threshold);

#endif