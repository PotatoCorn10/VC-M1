#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP3/histogram.h"

int main(int argc, char* argv[]) {
    pgm_file image;

    /* Arguments */
    if ( argc != 3 ){
      printf("\nUsage: %s file_in file_out \n\n", argv[0]);
      exit(0);
    }

    /* Opening input file */
    image = read_pgm(argv[1]);

    // Modify the image by applying a histogram equalization
    pgm_file equalized_image = histogram_equalization(image);

    /* Write output file */
    write_pgm(equalized_image, argv[2]);

    return 0;
}
