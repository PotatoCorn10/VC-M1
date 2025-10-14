
#include <stdio.h>
#include <stdlib.h>

#include "../Utils/types.h"
#include "../Utils/Util.h"


histogram_t compute_histogram(pgm_file image) {

    histogram_t histogram;
    histogram.size = image.maxval + 1;
    histogram.histogram = (int*)malloc(histogram.size*sizeof(int));

    for(int i = 0; i < histogram.size; ++i){
      histogram.histogram[i] = 0;
    }
    
    for(int i = 0; i < image.rows*image.rows; ++i){
      ++histogram.histogram[(int)image.graymap[i]];
    }

    return histogram;

}

histogram_t compute_histogram_ppm(ppm_file image) {

  pgm_file image_gray;

  rgb_to_gray(image, &image_gray, 1);

  histogram_t histogram = compute_histogram(image_gray);
    
  return histogram;
}


pgm_file histogram_stretching(pgm_file image) {

    double minval = 255.0;
    double maxval = 0.0;

    // find image max and min values
    for(int i = 0; i < image.rows*image.cols; ++i){
      if(((double)image.graymap[i]) < minval) minval = (double)image.graymap[i];
      if(((double)image.graymap[i]) > maxval) maxval = (double)image.graymap[i];
    }

    for(int i = 0; i < image.rows*image.cols; ++i){
      image.graymap[i] = (int)(((((double)image.graymap[i]) - minval)/(maxval - minval))*(double)image.maxval);
    }

    pgm_file output_image;

    output_image = image;

    return output_image;
}

ppm_file histogram_stretching_ppm(ppm_file image) {

  pgm_file image_gray;
  pgm_file image_gray_stretched;

  rgb_to_gray(image, &image_gray, 1);
  rgb_to_gray(image, &image_gray_stretched, 1);

  image_gray_stretched = histogram_stretching(image_gray_stretched);

  for(int i = 0; i < image.rows*image.cols; ++i){
    double old_val =(double)image_gray.graymap[i];
    double new_val =(double)image_gray_stretched.graymap[i];
    double factor;
    if(old_val == 0) {
      factor = 0;
    } else{
      factor = new_val/old_val;
    }
    int r = (int)(((double)image.pixmap[i].red) * factor);
    int g = (int)(((double)image.pixmap[i].green) * factor);
    int b =  (int)(((double)image.pixmap[i].blue) * factor);
    if(r > image.maxval) r = image.maxval;
    if(g > image.maxval) g = image.maxval;
    if(b > image.maxval) b = image.maxval;

    image.pixmap[i].red = r;
    image.pixmap[i].green = g;
    image.pixmap[i].blue = b;
  }

  ppm_file output_image;

  output_image = image;

  return output_image;
}

pgm_file histogram_equalization(pgm_file image) {

    histogram_t hist = compute_histogram(image);


    for(int i = 0; i < image.rows*image.cols; ++i){
      double factor = ((double)image.maxval)/(double)(image.rows*image.cols);
      double sum = 0;
      for(int j = 0; j < image.graymap[i]; ++j){
        sum += (double)hist.histogram[j];
      }
      image.graymap[i] = ((int)(factor * sum));
    }

    pgm_file output_image;

    output_image = image;

    return output_image;
}

ppm_file histogram_equalization_ppm(ppm_file image){
  pgm_file image_gray;
  pgm_file image_gray_equalized;

  rgb_to_gray(image, &image_gray, 1);
  rgb_to_gray(image, &image_gray_equalized, 1);

  image_gray_equalized = histogram_equalization(image_gray_equalized);

  for(int i = 0; i < image.rows*image.cols; ++i){
    double old_val =(double)image_gray.graymap[i];
    double new_val =(double)image_gray_equalized.graymap[i];
    double factor;
    if(old_val == 0) {
      factor = 0;
    } else{
      factor = new_val/old_val;
    }
    int r = (int)(((double)image.pixmap[i].red) * factor);
    int g = (int)(((double)image.pixmap[i].green) * factor);
    int b =  (int)(((double)image.pixmap[i].blue) * factor);
    if(r > image.maxval) r = image.maxval;
    if(g > image.maxval) g = image.maxval;
    if(b > image.maxval) b = image.maxval;

    image.pixmap[i].red = r;
    image.pixmap[i].green = g;
    image.pixmap[i].blue = b;
  }

  ppm_file output_image;

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