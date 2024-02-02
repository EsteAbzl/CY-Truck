#include "main.h"

int main(int argc, char *argv[]) {
  if (argc - 1 == 2) {
  } else {
    printf("C ERROR: Wrong number of arguments");
    exit(1);
  }

  FILE *fData = fopen(argv[1], "r");
  
  if(strcmp(argv[2], "-d1") == 0){

  }
  else if(strcmp(argv[2], "-d2") == 0){

  }
  else if(strcmp(argv[2], "-l") == 0){

  }
  else if(strcmp(argv[2], "-t") == 0){
    T_Init(fData);
  }
  else if(strcmp(argv[2], "-s") == 0){
    S_Init(fData);
  }
  else{
    printf("C ERROR: Option wasn't found");
    exit(2);
  }
 

  fclose(fData);
  

  return 0;
}
