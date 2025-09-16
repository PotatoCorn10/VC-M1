#include <stdlib.h>

#include "Utils/types.h"
#include "Utils/Util.h"

int main(int argc, char* argv[])
    {
    pgm_file image;

    /* Arguments */
    if ( argc != 3 ){
      printf("\nUsage: %s file_in file_out \n\n", argv[0]);
      exit(0);
    }

    /* Opening input file */
    image = read_pgm(argv[1]);

    // TODO: What do these lines do?
    if (image.magic_number == '2') {
        image.magic_number = '5';
    } else if (image.magic_number == '5') {
        image.magic_number = '2';
    }

    /* Write output file */
    write_pgm(image, argv[2]);

    return 0;
}
