#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP1/TP1_funcs.h"

int main(int argc, char* argv[]) {
    // Image definitions
    ppm_file image;
    pgm_file mask;
    pam_file image_pam;

    /* Arguments */
    if ( argc != 4 ){
      printf("\nUsage : %s file_in mask file_pam \n\n", argv[0]);
      exit(0);
    }

    // if(argc == 4) {
    //   // convert char * to float
    //   brightness = atof(argv[3]);
    // }

    /* Opening input file */
    image = read_ppm(argv[1]);

    // Opening mask file
    mask = read_pgm(argv[2]);

    // Conversion
    ppm_to_pam(image, mask, &image_pam);

    /* Write output file */
    write_pam(image_pam, argv[3]);

    return 0;
}
