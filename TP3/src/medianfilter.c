#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP3/filters.h"

int main(int argc, char* argv[]) {
    pgm_file image, smoothed_image;

    /* Arguments */
    if ( argc !=4 && argc != 5 ){
      printf("\nUsage: %s file_in file_out filter_size N=1\n\n", argv[0]);
      exit(0);
    }

    /* Opening input file */
    image = read_pgm(argv[1]);

    // filter size
    int filter_size = atoi(argv[3]);

    // How many times is the program going to smooth?
    int N = 1;
    if (argc == 5) {
        N = atoi(argv[4]);
    }

    smoothed_image = median_filter(image, filter_size, N);

    /* Write output file */
    write_pgm(smoothed_image, argv[2]);

    return 0;
}
