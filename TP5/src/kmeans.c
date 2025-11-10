#include <stdlib.h>
#include <string.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP5/TP5_funcs.h"

int main(int argc, char *argv[]) {
    if (argc != 8) {
        printf("\nUsage: %s input.ppm output.ppm K init stop location seed\n"
                       "output.ppm==-1 for autonaming\n"
                       "J is the number of clusters\n"
                       "init is the initialization strategy\n"
                       "stop is the end condition strategy\n"
                       "location==0: do not use location\n"
                       "seed==0: for random initialization\n",
               argv[0]);
        exit(0);
    }

    /* Opening input file */
    ppm_file image = read_ppm(argv[1]);

    // Parsing arguments
    int K = atoi(argv[3]);
    int init = atoi(argv[4]);
    int stop = atoi(argv[5]);
    double location = strtod(argv[6],NULL);
    int seed_value = atoi(argv[7]);

    // Initializing random seed
    srand(seed_value);

    // create output filename if necessary
    char output_filename[512];

    if (atoi(argv[2]) == -1) {
        sprintf(output_filename, "results/%c_%d_%d_%d_%f_%d.ppm",
            argv[1][7], // hack: use first letter of image to create output (f for frog in this TP)
            K, init, stop, location, seed_value);

    } else {
        // copy string
        memcpy(output_filename, argv[2], 512);
    }
    printf("Result will be stored in %s\n", output_filename);

    ppm_file kmeans_image = kmeans(image, K, init, stop, location);

    write_ppm(kmeans_image, output_filename);

    return 0;
}
