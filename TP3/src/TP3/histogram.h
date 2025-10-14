#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "../Utils/types.h"

histogram_t compute_histogram(pgm_file);

histogram_t compute_histogram_ppm(ppm_file);

pgm_file histogram_stretching(pgm_file);

ppm_file histogram_stretching_ppm(ppm_file);

pgm_file histogram_equalization(pgm_file);

ppm_file histogram_equalization_ppm(ppm_file);

// Stores a histogram into a csv file format
void save_histogram(histogram_t histogram, char *path);


#endif
