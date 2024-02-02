#include "process.h"

DataLine* init_ReadLine(FILE* fFile){
  if(fFile == NULL){
    printf("%s: pFile isn't properly given", __func__);
    exit(4);
  }

  // Set the cursor to the start of the file
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
  char string[COLUMN_SIZE];  // column being read
  int i = 0;        // 'c' caracter position in 'string'
  int column = 0;

  while(c != '\n' && c != EOF){
    c = getc(fFile);
      
    if(c == ';' || c == '\n' || c == EOF){
    string[i] = '\0';
    
    switch (column) {
    case ROUTE_ID:
        pLine->route_ID = atoi(string);
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
    if(i >= COLUMN_SIZE){
      printf("%s: The number of caracter of the column %d execced %d", __func__, column++, COLUMN_SIZE);
      exit(6);
    }
  }

  return (string[0] != EOF); // Part of a little complicated way to know when we trully hit the EOF
}


void init_Top(Top_T* pTop){
  pTop->pFist = NULL;
  pTop->size = 0;
  pTop->i_ValMin = 0;
  pTop->c_ValMin[0] = 0;
}

NodeTopT *create_NodeTopT(NodeAvlChar* pNodeAvlTown){
  NodeTopT* pNew = malloc(sizeof(NodeTopT));
  if(CHECK_PTR(pNew)) exit(5);

  pNew->i_Val = 0;
  pNew->c_Val[0] = 0;
  
  sprintf(pNew->caption, "%s", pNodeAvlTown->pTown->name);

  pNew->nPath = pNodeAvlTown->pTown->nPath;
  pNew->nFirstPath = pNodeAvlTown->pTown->nStartingTown;

  pNew->pNext = NULL;

  return pNew;
}

void free_NodeTopT(NodeTopT* pNode){
  if(pNode){
    free_NodeTopT(pNode->pNext);

    free(pNode);
  }
}

NodeTopT* insertTopT(NodeTopT* pNode, int val, NodeAvlChar* pNodeAvlTown){
  NodeTopT* pNew = NULL;

  if(CHECK_PTR(pNode)){
    pNew = create_NodeTopT(pNodeAvlTown);
    pNew->i_Val = val;
  }
  else if(val > pNode->i_Val){
    pNew = create_NodeTopT(pNodeAvlTown);
    pNew->i_Val = val;
    pNew->pNext = pNode;
  }
  else{
    pNode->pNext = insertTopT(pNode->pNext, val, pNodeAvlTown);
    pNew = pNode;
  }

  return pNew;
}

void popLastTopT(NodeTopT* pNode, int* valMin){
  if(CHECK_PTR(pNode)) exit(4);
  if(CHECK_PTR(pNode->pNext)) exit(4);

  if(CHECK_PTR(pNode->pNext->pNext)){
    free(pNode->pNext);
    pNode->pNext = NULL;
    *valMin = pNode->i_Val;
  }
  else{
    popLastTopT(pNode->pNext, valMin);
  }
}

void compute_t_Top(NodeAvlChar* pTree, Top_T* pTop){
  if(pTree){

    if(pTop->size < 10){
      pTop->pFist = insertTopT(pTop->pFist, pTree->pTown->nPath, pTree);
      pTop->size++;
    }
    else if(pTree->pTown->nPath > pTop->i_ValMin){
      pTop->pFist = insertTopT(pTop->pFist, pTree->pTown->nPath, pTree);
      popLastTopT(pTop->pFist, &pTop->i_ValMin);
    }

    compute_t_Top(pTree->pL, pTop);
    compute_t_Top(pTree->pR, pTop);
  }
}

void print_t_Top(Top_T* pTop){
  NodeTopT* pTrav = pTop->pFist;
  while(pTrav){
    printf("%s;%d;%d\n", pTrav->caption, pTrav->nPath, pTrav->nFirstPath);
    pTrav = pTrav->pNext;
  }
}

void t_Top(AvlChar* pAvlTown){
  Top_T top;
  init_Top(&top);

  compute_t_Top(pAvlTown->pRoot, &top);
  print_t_Top(&top);

  free_NodeTopT(top.pFist);
}


void t_Process(FILE* fFile){
  if(CHECK_PTR(fFile)) exit(4);

  DataLine* pLine = init_ReadLine(fFile);
  AvlChar* pAvlTown = init_AvlChar();

  NodeAvlChar* pTempNodeTown = NULL;

// STEP 1 : Fill the AVL
  while(readLine(fFile, pLine)){
    pTempNodeTown = NULL;
    
    // Town A
    if(pLine->step_ID == 1){
      pTempNodeTown = isInAvlChar(pAvlTown->pRoot, pLine->town_A);
      if(CHECK_PTR(pTempNodeTown)){
        add_AvlChar(pAvlTown, NULL, create_Town(pLine->town_A, pLine->route_ID), pLine->town_A);
      
        pTempNodeTown = isInAvlChar(pAvlTown->pRoot, pLine->town_A);
      }
      else{
        if(!isInAvlBasicInt(pTempNodeTown->pTown->AvlPath->pRoot, pLine->route_ID)){
          add_AvlBasicInt(pTempNodeTown->pTown->AvlPath, pLine->route_ID);

          pTempNodeTown->pTown->nPath++;
        }
      }
      
      pTempNodeTown->pTown->nStartingTown++;
      pTempNodeTown = NULL;
    }

    // Town B
    pTempNodeTown = isInAvlChar(pAvlTown->pRoot, pLine->town_B);
    if(CHECK_PTR(pTempNodeTown)){
      add_AvlChar(pAvlTown, NULL, create_Town(pLine->town_B, pLine->route_ID), pLine->town_B);

    }
    else{
      if(!isInAvlBasicInt(pTempNodeTown->pTown->AvlPath->pRoot, pLine->route_ID)){
        add_AvlBasicInt(pTempNodeTown->pTown->AvlPath, pLine->route_ID);

        pTempNodeTown->pTown->nPath++;
      }
    }
  }

// STEP 2 : Print the top 10
  t_Top(pAvlTown);

  free_AvlChar(pAvlTown);
  free(pLine);
}



/*
void T_Init(FILE* fData){
  if (fData == NULL) {
    exit(122);
  }
  DataLine* pLine = init_ReadLine(fData);
  int *h = 0;
  AvlTown* pTown = NULL;
  AvlTown* pNew = malloc(sizeof(AvlTown));
  if (CHECK_PTR(pNew)) exit (1);

  // 
  // PASS 1 : FILL THE AVL
  //
  while (readLine(fData, pLine)) {
    // read the current line
    char* townName = malloc(sizeof(char)*50);
    if (CHECK_PTR(townName)) exit (220);
    townName = strcpy(townName, pLine->town_B);
    AvlTown* pNew = NULL;

    // check if the town is logged
    AvlTown* pTemp = isInAvlTown(pTown, townName);
    if (pTown == NULL) {
      // case 1 : the AVL isn't initialized
      pTown = createAvlTown(townName);
      pTown->nPass++;
      if (pLine->step_ID == 1) pTown->nFirst++;
    } else if (pTemp == NULL) {
      // case 2 : the town isn't logged
      pTown = addAvlTown(pTown, townName);
      pNew = isInAvlTown(pTown, townName);
      pNew->nPass++;
      if (pLine->step_ID == 1) pNew->nFirst++;
    } else {
      // case 3 : the town was logged, simply append
      pTemp->nPass++;
      if (pLine->step_ID == 1) pTemp->nFirst++;
    }
  }
  T_Process(pTown);
}


void T_Process(AvlTown* pTown) {
  if (pTown != NULL) {
    T_Process(pTown->pL);
    printf("%s, %i, %i\n", pTown->name, pTown->nPass, pTown->nFirst);
    T_Process(pTown->pR);
  }
}


void T2_Init(FILE* fData){
  if (fData == NULL) {
    exit(122);
  }
  DataLine* pLine = init_ReadLine(fData);
  int *h = 0;
  AvlTown* pTown = NULL;
  AvlTown* pNew = malloc(sizeof(AvlTown));
  if (CHECK_PTR(pNew)) exit (1);

  // 
  // PASS 1 : FILL THE AVL
  //
  while (readLine(fData, pLine)) {
    // read the current line
    char* townName = malloc(sizeof(char)*50);
    if (CHECK_PTR(townName)) exit (220);
    townName = strcpy(townName, pLine->town_B);
    AvlTown* pNew = NULL;

    // check if the town is logged
    AvlTown* pTemp = isInAvlTown(pTown, townName);
    if (pTown == NULL) {
      // case 1 : the AVL isn't initialized
      pTown = createAvlTown(townName);
      pTown->nPass++;
      char* driverName = malloc(sizeof(char)*50);
      if (CHECK_PTR(driverName)) exit (200);
      driverName = strcpy(driverName, pLine->name);
      pTown->pDrivers = createAvlDriver(driverName);
    } else if (pTemp == NULL) {
      // case 2 : the town isn't logged
      pTown = addAvlTown(pTown, townName);
      pNew = isInAvlTown(pTown, townName);
      pNew->nPass++;
      char* driverName = malloc(sizeof(char)*50);
      if (CHECK_PTR(driverName)) exit (200);
      driverName = strcpy(driverName, pLine->name);
      pNew->pDrivers = createAvlDriver(driverName);
    } else {
      // case 3 : the town was logged, simply append
      pTemp->nPass++;
      char* driverName = malloc(sizeof(char)*50);
      if (CHECK_PTR(driverName)) exit (200);
      driverName = strcpy(driverName, pLine->name);
      pTemp->pDrivers = addAvlDriver(pTemp->pDrivers, driverName);
    }


    // If on the first step of a route, also log the starting town
    if (pLine->step_ID == 1) {
      // read the current line
      char* townName = malloc(sizeof(char)*50);
      if (CHECK_PTR(townName)) exit (220);
      townName = strcpy(townName, pLine->town_A);
      AvlTown* pNew = NULL;

      // check if the town is logged
      AvlTown* pTemp = isInAvlTown(pTown, townName);
      if (pTown == NULL) {
        // case 1 : the AVL isn't initialized
        pTown = createAvlTown(townName);
        pTown->nPass++;
        char* driverName = malloc(sizeof(char)*50);
        if (CHECK_PTR(driverName)) exit (200);
        driverName = strcpy(driverName, pLine->name);
        pTown->pDrivers = createAvlDriver(driverName);
      } else if (pTemp == NULL) {
        // case 2 : the town isn't logged
        pTown = addAvlTown(pTown, townName);
        pNew = isInAvlTown(pTown, townName);
        pNew->nPass++;
        char* driverName = malloc(sizeof(char)*50);
        if (CHECK_PTR(driverName)) exit (200);
        driverName = strcpy(driverName, pLine->name);
        pNew->pDrivers = createAvlDriver(driverName);
      } else {
        // case 3 : the town was logged, simply append
        pTemp->nPass++;
        char* driverName = malloc(sizeof(char)*50);
        if (CHECK_PTR(driverName)) exit (200);
        driverName = strcpy(driverName, pLine->name);
        pTemp->pDrivers = addAvlDriver(pTemp->pDrivers, driverName);
      }
    }
  }
  T2_Process(pTown);
}


void T2_Process(AvlTown* pTown) {
  if (pTown != NULL) {
    T2_Process(pTown->pL);
    printf("%s, %i, %i\n", pTown->name, pTown->nPass, avlDriverNodeCount(pTown->pDrivers));
    T2_Process(pTown->pR);
  }
}


// Holy crap finally some good code
void S_Init(FILE* fData){
  if (fData == NULL) {
    exit(122);
  }
  DataLine* pLine = init_ReadLine(fData);
  int *h = 0;
  AvlRoute* pRoute = NULL;
  AvlRoute* pNew = malloc(sizeof(AvlRoute));
  if (CHECK_PTR(pNew)) exit (1);

  // 
  // PASS 1 : FILL THE AVL
  //
  while (readLine(fData, pLine)) {
    // read the current line
    long routeID = pLine->route_ID;
    AvlRoute* pTemp = isInAvlRoute(pRoute, routeID);
    float dist = pLine->distance;
    // Insert the data into the tree
    if (pRoute == NULL) {
      pRoute = createAvlRoute(routeID);
      pRoute->nSteps = 1;
      pRoute->distTot = dist;
      pRoute->distMax = dist;
      pRoute->distMin = dist;
    } else if (pTemp == NULL) {
      pRoute = addAvlRoute(pRoute, routeID);
      pNew = isInAvlRoute(pRoute, routeID);
      pNew->distTot = dist;
      pNew->distMax = dist;
      pNew->distMin = dist;
      pNew->nSteps++;
    } else {
      pTemp->nSteps++;
      //printf("To be added : %f\n", dist);
      //printf("Current Value : %f\n", pTemp->distMax);
      //printf("Should be : %f\n", pTemp->distMax + dist);
      if (pTemp->distMin > dist) pTemp->distMin = dist;
      if (pTemp->distMax < dist) pTemp->distMax = dist;
      pTemp->distTot += dist;
      //printf("Is : %f\n", pTemp->distMax);
    }
  }
  //
  // PASS 2 : COMPUTE AVERAGES AND PRINT
  //
  S_Process(pRoute);
}

void S_Process(AvlRoute* pRoute) {
  if (pRoute != NULL) {
    S_Process(pRoute->pL);
    printf("%d:%f:%f:%f\n", pRoute->id, pRoute->distTot / pRoute->nSteps, pRoute->distMax, pRoute->distMin);
    S_Process(pRoute->pR);
  }
}
// RIPBOZO PACKWATCH REST IN PISS YOU WONT BE MISSED
// AWK REPLACED YOU YOU USELESS PILE OF HACKY CRAP
/*AvlDriver *D2(FILE *fData) {
  if (fData == NULL) {
    exit(122);
  }
  AvlDriver *pDriver = NULL;
  DataLine* pLine =  init_ReadLine(fData);
  int *h = 0;
  AvlDriver* pNew = malloc(sizeof(AvlDriver*));
  if (CHECK_PTR(pNew)) exit (1);
  while(readLine(fData, pLine)){
    char * copy = malloc(sizeof(char)*32);
    copy = strcpy(copy, pLine->name);
    AvlDriver *pTemp = isInAvlDriver(pDriver,copy);
    if(pDriver == NULL){
      //printf("DEBUG1\n");
      pDriver = createAvlDriver(copy);
      pDriver->totalDist = pLine->distance;
      // printf("%s,%f\n",pDriver->name,pDriver->totalDist);
      //printf("DEBUG2\n");
    } else if (pTemp == NULL){
      //printf("DEBUG3\n");
      pDriver = addAvlDriver(pDriver, copy, pNew);
      //printf("%s\n", pDriver->pL->name);
      //printf("DEBUG10\n");
      // TODO FIX THIS THIS IS AWFUL AND INEFFICIENT
      // pTemp = isInAvlDriver(pDriver, copy);
      //printf("DEBUG11\n");
      if(CHECK_PTR(pNew)) exit (69);
      pNew->totalDist = pLine->distance;
      //printf("DEBUG12\n");
      // printf("%s,%f\n", pTemp->name, pTemp->totalDist);
      //printf("DEBUG4\n");
    } else {
        //printf("DEBUG5\n");
        pTemp->totalDist += pLine->distance;
        // printf("%s,%f\n",pTemp->name,pTemp->totalDist);
        //printf("existe deja\n");
        //printf("DEBUG6\n");
    }
  }
  infixe(pDriver);
  free(pLine);
}
*/


