#ifndef TYPES_H
#define TYPES_H


// A gray byte in an image, represents an intensity.
typedef unsigned char gray;
typedef unsigned char bit;
// A signed float to store the derivative value
typedef float derivative;


// A PGM file, containing a gray map and its metadata
typedef struct {
  gray *graymap;
  char magic_number;
  int rows;
  int cols;
  int maxval;
} pgm_file;

// A pixel in an image, represents its 3 channels R, G and B
typedef struct {
  bit red;
  bit green;
  bit blue;
} pixel;

// A PPM file, containing a pixel map and its metadata
typedef struct {
  pixel *pixmap;
  char magic_number;
  int rows;
  int cols;
  int maxval;
} ppm_file;

// A structure to contain the information of a histogram
typedef struct {
  int *histogram;
  unsigned int size;
} histogram_t;

// A container for a gradient image, containing an image
// for the x-derivative and one for the y-derivative
typedef struct {
  derivative *derivative_x;
  derivative *derivative_y;
  int rows;
  int cols;
} gradient_image;

// A container for a gradient magnitude and angle, containing an image
// for the magnitude and one for the angle
typedef struct {
  float *magnitude;
  float *angle;
  int rows;
  int cols;
} magnitude_angle_image;

#endif
