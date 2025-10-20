#ifndef GRADIENTS_H
#define GRADIENTS_H

#include "../Utils/types.h"

// TODO: compute the gradients of the input image
gradient_image compute_gradients(pgm_file image);

// TODO: compute the magnitude and angle of the gradients
magnitude_angle_image compute_magnitude_angle(gradient_image gradients);

// TODO: map gradients into an image that can be viewed [0,255]
pgm_file map_gradients_magnitude(magnitude_angle_image magnitude);

#endif