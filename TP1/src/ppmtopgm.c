#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP1/TP1_funcs.h"

int main(int argc, char* argv[]) {
    // Image definitions
    ppm_file image;
    pgm_file image_gray;

    /* Arguments */
    if ( argc != 3 && argc != 4 ){
      printf("\nUsage : %s file_in file_gray (brightness coeff) \n\n", argv[0]);
      exit(0);
    }

    // Parse Brightness
    float brightness = 1;
    if(argc == 4) {
      // convert char * to float
      brightness = atof(argv[3]);
    }

    /* Opening input file */
    image = read_ppm(argv[1]);

    // Conversion
    rgb_to_gray(image, &image_gray, brightness);

    /* Write output file */
    write_pgm(image_gray, argv[2]);

    return 0;
}
