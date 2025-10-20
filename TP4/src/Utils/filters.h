#ifndef FILTERS_H
#define FILTERS_H

#include "../Utils/types.h"

// TODO: binomial filter with different sizes (3,5)
pgm_file binomial_filter(pgm_file image, int filter_size, int iterations);

pgm_file add_padding(pgm_file image, int filter_size);

// TODO: median filter with different sizes (3,5)
pgm_file median_filter(pgm_file image, int filter_size, int iterations);

#endif