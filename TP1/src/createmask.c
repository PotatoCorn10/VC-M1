#include <stdlib.h>
#include <math.h>

#include "Utils/types.h"
#include "Utils/Util.h"

#include "TP1/TP1_funcs.h"

int get_val(int j, int collumns){
  return 255 - ((abs(j*2 - collumns)) * 255)/collumns;
}


// Create a mask that highlights the center
// Usage: output_fname rows cols
int main(int argc, char* argv[]){

  if(argc != 4){
    perror("Incorrect Usage");
    exit(EXIT_FAILURE);
  }

  pgm_file image;

  image.magic_number = 6;
  image.rows = atoi(argv[2]);
  image.cols = atoi(argv[3]);
  image.maxval = 255;
  
  image.graymap = (gray*) malloc(sizeof(gray)*image.rows*image.cols);

  for(int i = 0; i < image.rows; ++i){
    for(int j = 0; j < image.cols; ++j){
      image.graymap[i * image.cols + j] = get_val(j, image.cols);
    }
  }

  write_pgm(image, argv[1]);

}