#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"
#include "Utils/filters.h"

#include "TP4/gradients.h"
#include "TP4/canny.h"


int main(int argc, char* argv[]) {
    pgm_file image;

    /* Arguments */
    if ( argc !=7 ){
      printf("\nUsage: %s file_in file_out filter_size N high_threshold low_threshold\n\n", argv[0]);
      exit(0);
    }

    // Opening input file
    image = read_pgm(argv[1]);

    // filter size
    int filter_size = atoi(argv[3]);
    int N = atoi(argv[4]);

    // Canny Thresholds
    int high_threshold = atoi(argv[5]);
    int low_threshold = atoi(argv[6]);

    // Smooth image
    pgm_file smoothed_image;
    smoothed_image = binomial_filter(image, filter_size, N);

    // Computing gradients
    gradient_image gradients;
    gradients = compute_gradients(smoothed_image);

    // Compute magnitudes and angles
    magnitude_angle_image magnitude_angle;
    magnitude_angle = compute_magnitude_angle(gradients);

    // Non-maximum suppression of the magnitudes using the angle direction
    magnitude_angle_image max_magnitude_angle;
    max_magnitude_angle = directed_non_maximum_suppression(magnitude_angle);

    // Hysteresis thresholding
    pgm_file canny_edges;
    canny_edges = hysteresis_thresholding(max_magnitude_angle, high_threshold, low_threshold);

    /* Write output file */
    write_pgm(canny_edges, argv[2]);
    return 0;
}
