#include <stdlib.h>
#include <string.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP3/histogram.h"

int main(int argc, char* argv[]) {
    /* Arguments */
    if ( argc !=3 ){
      printf("\nUsage: %s file_in file_histogram_out \n\n", argv[0]);
      exit(0);
    }


    if(argv[1][strlen(argv[1]) - 2] == 'g'){
      pgm_file image;

      /* Opening input file */
      image = read_pgm(argv[1]);

      // Compute histogram
      histogram_t histogram = compute_histogram(image);

      /* Write output file */
      save_histogram(histogram, argv[2]);
    } else if (argv[1][strlen(argv[1]) - 2] == 'p'){
      ppm_file image;

      /* Opening input file */
      image = read_ppm(argv[1]);

      // Compute histogram
      histogram_t histogram = compute_histogram_ppm(image);

      /* Write output file */
      save_histogram(histogram, argv[2]);
    } else {
      printf("Unsupported input file format");
      exit(0);
    }
    return 0;
}
