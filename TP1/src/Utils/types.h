#ifndef TYPES_H
#define TYPES_H


// A gray byte in an image, represents an intensity.
typedef unsigned char gray;
typedef unsigned char bit;

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

typedef struct {
  bit red;
  bit green;
  bit blue;
  bit alpha;
} pam_pixel;

// A PPM file, containing a pixel map and its metadata
typedef struct {
  pixel *pixmap;
  char magic_number;
  int rows;
  int cols;
  int maxval;
} ppm_file;

typedef struct {
  pam_pixel *pammap;
  char magic_number;
  int rows;
  int cols;
  int maxval;
  int depth;
  // char tupltype[64];
} pam_file;


// P7
// WIDTH 227
// HEIGHT 149
// DEPTH 3
// MAXVAL 255
// TUPLTYPE RGB
// ENDHDR


#endif
