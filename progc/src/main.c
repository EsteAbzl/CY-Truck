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
  
  /* redirection into the right process
  if()
  */

  /* =-=-=-= TEST ZONE =-=-=-= */

  // AvlDriver* Result = D2(fData);
  //S_Init(fData);
  //T2_Init(fData);
  T_Init(fData);

  /* =-=-=-=-----------=-=-=-= */
  

  //printf("\n---End of %s process---\n\n", argv[2]);

  return 0;
}
