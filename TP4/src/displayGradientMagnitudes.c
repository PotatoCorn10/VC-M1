#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"
#include "Utils/filters.h"

#include "TP4/gradients.h"

int main(int argc, char* argv[]) {
    pgm_file image;

    /* Arguments */
    if ( argc !=5 ){
      printf("\nUsage: %s file_in file_out filter_size N\n\n", argv[0]);
      exit(0);
    }

    // Opening input file
    image = read_pgm(argv[1]);

    // filter size
    int filter_size = atoi(argv[3]);
    int N = atoi(argv[4]);

    // Smooth image
    pgm_file smoothed_image;
    smoothed_image = binomial_filter(image, filter_size, N);

    // Computing gradients
    gradient_image gradients;
    gradients = compute_gradients(smoothed_image);

    // Compute magnitudes and angles
    magnitude_angle_image magnitude_angle;
    magnitude_angle = compute_magnitude_angle(gradients);

    // Map gradients to visible range
    pgm_file mapped_gradient_magnitudes;
    mapped_gradient_magnitudes = map_gradients_magnitude(magnitude_angle);

    /* Write output file */
    write_pgm(mapped_gradient_magnitudes, argv[2]);
    return 0;
}
