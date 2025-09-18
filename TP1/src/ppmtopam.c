#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP1/TP1_funcs.h"

int main(int argc, char* argv[]) {
    // Image definitions
    ppm_file image;
    pam_file image_pam;

    /* Arguments */
    if ( argc != 3 ){
      printf("\nUsage : %s file_in file_pam (alpha coeff) \n\n", argv[0]);
      exit(0);
    }

    int alpha = 255;

    // if(argc == 4) {
    //   // convert char * to float
    //   brightness = atof(argv[3]);
    // }

    /* Opening input file */
    image = read_ppm(argv[1]);

    // Conversion
    ppm_to_pam(image, &image_pam, alpha);

    /* Write output file */
    write_pam(image_pam, argv[2]);

    return 0;
}
