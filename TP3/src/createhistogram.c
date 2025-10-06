#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP3/histogram.h"

int main(int argc, char* argv[]) {
    pgm_file image;

    /* Arguments */
    if ( argc !=3 ){
      printf("\nUsage: %s file_in file_histogram_out \n\n", argv[0]);
      exit(0);
    }

    // Opening input file
    image = read_pgm(argv[1]);

    // Computing histogram
    histogram_t histogram = compute_histogram(image);

    // Saving histogram
    save_histogram(histogram, argv[2]);

    return 0;
}
