#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP3/histogram.h"

int main(int argc, char* argv[]) {
    if(argv[1][strlen(argv[1]) - 2] == 'g'){
      pgm_file image;

      /* Opening input file */
      image = read_pgm(argv[1]);

      // Modify the image by applying a histogram stretching
      pgm_file stretched_image = histogram_equalization(image);

      /* Write output file */
      write_pgm(stretched_image, argv[2]);
    } else if (argv[1][strlen(argv[1]) - 2] == 'p'){
      ppm_file image;

      /* Opening input file */
      image = read_ppm(argv[1]);

      // Modify the image by applying a histogram stretching
      ppm_file stretched_image = histogram_equalization_ppm(image);

      /* Write output file */
      write_ppm(stretched_image, argv[2]);
    } else {
      printf("Unsupported input file format");
      exit(0);
    }

    return 0;
}
