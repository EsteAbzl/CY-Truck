#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  if(argc-1 == 2){
    printf("\n---Entering %s process---\n", argv[2]);
  }
  else{
    printf("C ERROR: Wrong number of arguments");
    exit(1);
  }

  FILE* fData = NULL;
  //if((fopen()))

  // Temporary code, show how the arguments work --
  printf("There is %d argument to %s:", argc-1, argv[0]);
  for(int i = 1; i<argc; i++){
    printf("\n%d: %s", i, argv[i]);
  }
  //--

  
  printf("\n---End of %s process---\n\n", argv[2]);
  
  return 0;
}