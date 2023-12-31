#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  if(argc-1 == 1){
    printf("\n---Entering %s process---\n", argv[1]);
  }
  

  // Temporary code, show how the arguments work --
  printf("There is %d argument to %s:", argc-1, argv[0]);
  for(int i = 1; i<argc; i++){
    printf("\n%d: %s", i, argv[i]);
  }
  //--

  
  if(argc-1 == 1){
    printf("\n---End of %s process---\n\n", argv[1]);
  }
  return 0;
}