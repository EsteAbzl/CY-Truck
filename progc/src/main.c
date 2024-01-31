#include "main.h"

int main(int argc, char *argv[]) {
  if (argc - 1 == 2) {
    //printf("\n---Entering %s process---\n", argv[2]);
  } else {
    printf("C ERROR: Wrong number of arguments");
    exit(1);
  }

  /*  Mode Ouverture :
        r lecture seul , w ecriture seul , a ajouter fin , a+
        lire et ecrire a la fin (si fichier existe pas il sera ajouter) ,r+ lire
        écrire (fichier DOIT etre créer), w+ pareil que r+ mais écrase tout. */
  FILE *fData = fopen(argv[1], "r");
  
  // Redirection into the right process
  if(strcmp(argv[2], "-d1") == 0){

  }
  else if(strcmp(argv[2], "-d2") == 0){

  }
  else if(strcmp(argv[2], "-l") == 0){

  }
  else if(strcmp(argv[2], "-t") == 0){

  }
  else if(strcmp(argv[2], "-s") == 0){

  }
  else{
    printf("C ERROR: Option wasn't found");
    exit(2);
  }
 

  /* =-=-=-= TEST ZONE =-=-=-= */

  // AvlDriver* Result = D2(fData);
  //S_Init(fData);
  //T2_Init(fData);
  T_Init(fData);

  /* =-=-=-=-----------=-=-=-= */// INCLUDES

  fclose(fData);
  

  //printf("\n---End of %s process---\n\n", argv[2]);

  return 0;
}
