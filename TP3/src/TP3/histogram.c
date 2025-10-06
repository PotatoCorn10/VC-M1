
#include <stdio.h>
#include <stdlib.h>

#include "../Utils/types.h"


histogram_t compute_histogram(pgm_file image) {

    printf("PLEASE IMPLEMENT compute_histogram\n");

    histogram_t histogram;
    histogram.size = 0;

    return histogram;

}


pgm_file histogram_stretching(pgm_file image) {

    printf("PLEASE IMPLEMENT histogram_stretching\n");

    pgm_file output_image;

    output_image = image;

    return output_image;
}

pgm_file histogram_equalization(pgm_file image) {

    printf("PLEASE IMPLEMENT histogram_equalization\n");

    pgm_file output_image;

    output_image = image;

    return output_image;
}


// Stores a histogram into a csv file format
void save_histogram(histogram_t histogram, char *path) {

  FILE *fp;
  fp = fopen(path, "w");

  if (fp == NULL) {
    printf("error in opening file %s\n", path);
    exit(1);
  }

  // first row with headers
  fprintf(fp, "Intensity, Count\n");

  // print the histogram values
  for (int i = 0; i < histogram.size; i++) {
    fprintf(fp, "%d,%d\n", i, histogram.histogram[i]);
  }

  fclose(fp);
}