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




void D2(FILE *fData, int line_number) {
  if (fData == NULL) {
    exit(4);
  }
  AvlDriver *pTemp = NULL;
  AvlDriver *pDriver = NULL;
  DataLine* pLine =  init_ReadLine(fData);
  while(readLine(fData, pLine)){
    if(pDriver == NULL){
        pDriver = createAvlDriver(pLine->name);
        pDriver->totalDist = pLine->distance;
    }
    else if(isInAvlDriver(pDriver,pLine->name)){
        pTemp = isInAvlDriver(pDriver,pLine->name);
        pTemp->totalDist += pLine->distance;
    }
    else{
        pDriver = addAvlDriver(pDriver,pLine->name);
        pTemp = isInAvlDriver(pDriver,pLine->name);
        pTemp->totalDist = pLine->distance;   
    }
  }
  free(pLine);

  AvlDriver * max , * min , * node;
  int content = 0;
  FIFO * file = malloc(sizeof(FIFO));
  if(file == NULL){
     exit(5);
  }
  while(!checkPtr(pDriver)){
    file = insertFIFO(file,pDriver);
    while(!checkPtr(file)){
      node = suprFIFO(file);
      if(checkLeftAvlDriver(node)){
        file=insertFIFO(file,node->pL);
      }
      if(checkRightAvlDriver(node)){
        file=insertFIFO(file,node->pR);
      }
      if(max == NULL){
        min = createAvlDriver(node->name);
        min->totalDist = node->totalDist;
        max = createAvlDriver(node->name);
        max->totalDist = node->totalDist;
        content++;
      }
      else if(content<10){
        max = addAvlDriver(max,node->name);
        pTemp = isInAvlDriver(max,node->name);
        pTemp->totalDist= node->totalDist;
        if(pTemp->totalDist < min->totalDist){
            min = pTemp;
        }
        content++;
      }
      else{
        if(pTemp->totalDist > min->totalDist){
            max = delAvlDriver(max,min->name);
            max = addAvlDriver(max,pTemp->name);
            pTemp = isInAvlDriver(max,pTemp->name);
            pTemp->totalDist= node->totalDist;
            min = pickmin_AvlDriver(max);          
        }
      }
    }
  }
}
  //d2 retourne max