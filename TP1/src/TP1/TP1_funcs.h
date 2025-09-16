#ifndef TP1_FUNCS_H
#define TP1_FUNCS_H

#include "../Utils/types.h"

// TODO: split the image into three channels
void split_channels(ppm_file image,
                    ppm_file *image_r, ppm_file *image_g, ppm_file *image_b);

// TODO: convert rgb to grayscale
void rgb_to_gray(ppm_file image, pgm_file *image_gray, float brightness);

#endif