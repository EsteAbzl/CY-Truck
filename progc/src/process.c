#include "process.h"

DataLine* init_ReadLine(FILE* fFile){
  if(fFile == NULL){
    printf("%s: pFile isn't properly given", __func__);
    exit(4);
  }

  // Set the cursor to the start af the file
  rewind(fFile);

  // Get rid of the first line
  while(fgetc(fFile) != '\n');

  DataLine* pNew = NULL;
  if((pNew = malloc(sizeof(DataLine))) == NULL){
    printf("%s: pNew allocation didn't work", __func__);
    exit(5);
  }

  pNew->route_ID = 0;
  pNew->step_ID = 0;
  pNew->town_A[0] = '\0';
  pNew->town_B[0] = '\0';
  pNew->distance = 0.0;
  pNew->name[0] = '\0';

  return pNew;
}

int readLine(FILE* fFile, DataLine* pLine){
  if(fFile == NULL){
      printf("%s: fFile isn't properly given", __func__);
      exit(4);
  }
  if(pLine == NULL){
      printf("%s: pLine isn't properly given", __func__);
      exit(4);
  }
  
  char c = 0;       // caracter being read
  char string[100]; // column being read
  int i = 0;        // 'c' caracter position in 'string'
  int column = 0;

  while(c != '\n' && c != EOF){
    c = getc(fFile);
      
    if(c == ';' || c == '\n' || c == EOF){
    string[i] = '\0';
    
    switch (column) {
    case ROUTE_ID:
        pLine->route_ID = atol(string);
        break;
    case STEP_ID:
        pLine->step_ID = atoi(string);
        break;
    case TOWN_A:
        sprintf(pLine->town_A, "%s", string);
        break;
    case TOWN_B:
        sprintf(pLine->town_B, "%s", string);
        break;
    case DISTANCE:
        pLine->distance = atof(string);
        break;
    case NAME:
        sprintf(pLine->name, "%s", string);
        break;
    }

    if(c == EOF){
      string[i] = c; // A little complicated way to know when we trully hit the EOF
    }
      
    column++;
    i=-1;
    }
    else{
      string[i] = c;
    }

    i++;
    if(i >= 100){
      printf("%s: The number of caracter of the column %d execced 100", __func__, column++);
      exit(6);
    }
  }

  return (string[0] != EOF); // Part of a little complicated way to know when we trully hit the EOF
}




void D1(FILE *fData, int line_number) {
  if (fData == NULL) {
    exit(4);
  }
  AvlDriver *pTemp = NULL;
  AvlDriver *pDriver = NULL;
  DataLine* pLine =  init_ReadLine(fData);
  while(readLine(fData, pLine)){
    if(pDriver == NULL){
        pDriver = createAvlDriver(pLine->name);
        pDriver->AvlPath = createAvlInt(pLine->route_ID);
        pDriver->nPath = 1;
    }
    if(isInAvlDriver(pDriver,pLine->name)){
        pTemp = isInAvlDriver(pDriver,pLine->name);
        pTemp->nPath++;
        pTemp->AvlPath = addAvlInt(pTemp->AvlPath,pLine->route_ID);    
    }
    else{
        pDriver->AvlPath = addAvlInt(pTemp->AvlPath,pLine->route_ID);
        pTemp = isInAvlDriver(pDriver,pLine->name);
        pTemp->nPath = 1;
        pTemp->AvlPath =  createAvlInt(pLine->route_ID);
        
    }
  }
  free(pLine);
}

void D2(FILE *fData, int line_number) {
  if (fData == NULL) {
    exit(4);
  }
  // Créer un arbre des personnes

  // boucle while pour lire les données de tout le fichier
  // recup la ligne
  // si la personne X dans arbre -> ajout
  // si la personnes est dedans incrementer la distance

  // free arbre ?
}
