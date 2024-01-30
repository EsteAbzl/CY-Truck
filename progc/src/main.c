#include <stdio.h>
#include <stdlib.h>
#define Size_Max 100

int main(int argc, char *argv[]) {
  if (argc - 1 == 2) {
    printf("\n---Entering %s process---\n", argv[2]);
  } else {
    printf("C ERROR: Wrong number of arguments");
    exit(1);
  }

  FILE *fData = NULL;
  // if((fopen()))
  //  FILE* fopen(const char* nomDuFichier, const char* modeOuverture);
  //  Mode Ouverture : r lecture seul , w ecriture seul , a ajouter fin , a+
  //  lire et ecrire a la fin (si fichier existe pas il sera ajouter) ,r+ lire
  //  écrire (fichier DOIT etre créer), w+ pareil que r+ mais écrase tout

  

  // Temporary code, show how the arguments work --
  printf("There is %d argument to %s:", argc - 1, argv[0]);
  for (int i = 1; i < argc; i++) {
    printf("\n%d: %s", i, argv[i]);
  }
  //--

  printf("\n---End of %s process---\n\n", argv[2]);

  return 0;
}
