#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "../Utils/types.h"

histogram_t compute_histogram(pgm_file image);

pgm_file histogram_stretching(pgm_file image);

pgm_file histogram_equalization(pgm_file image);

// Stores a histogram into a csv file format
void save_histogram(histogram_t histogram, char *path);


#endif
