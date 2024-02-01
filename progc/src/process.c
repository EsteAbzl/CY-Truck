#include "process.h"
#include "AVL/AVL_Town.h"
#include "AVL/AVL_TownSteps.h"

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
    if(i >= COLUMN_SIZE){
      printf("%s: The number of caracter of the column %d execced %d", __func__, column++, COLUMN_SIZE);
      exit(6);
    }
  }

  return (string[0] != EOF); // Part of a little complicated way to know when we trully hit the EOF
}


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
    } else if (pTemp == NULL) {
      // case 2 : the town isn't logged
      pTown = addAvlTown(pTown, townName);
      pNew = isInAvlTown(pTown, townName);
      pNew->nPass++;
    } else {
      // case 3 : the town was logged, simply append
      pTemp->nPass++;
    }
    // This is awful. It's disgusting. it works, and it's optimized,
    // but code-wise, it looks horrendous. We need to correctly log
    // the first town of a step. Yes, I hate it too. Yes, it works.
    if (pLine->step_ID == 1) { 
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
        pTown->nFirst++;
      } else if (pTemp == NULL) {
        // case 2 : the town isn't logged
        pTown = addAvlTown(pTown, townName);
        pNew = isInAvlTown(pTown, townName);
        pNew->nPass++;
        pNew->nFirst++;
      } else {
        // case 3 : the town was logged, simply append
        pTemp->nPass++;
        pTemp->nFirst++;
      }
    }
  }

  //
  // PASS 2 : Sort the data by the most visited towns
  //
  AvlTownsteps* sortedpTown = NULL;
  sortedpTown = T_Process1(pTown, sortedpTown);
  if (CHECK_PTR(sortedpTown)) exit (69);
  //
  // PASS 3 : Now, sort the ten most visited towns alphabetically.
  //
  int extract = 10;
  AvlTown* top10pTown = NULL;
  top10pTown = T_Process2(sortedpTown, top10pTown, &extract);
  inorderTown(top10pTown);
}


AvlTown* T_Process2(AvlTownsteps* pTown, AvlTown* targetpTown, int* extract) {
  if (CHECK_PTR(extract) || CHECK_PTR(pTown)) {
    return NULL;
  }
  
  if (!CHECK_PTR(pTown->pR)) targetpTown = T_Process2(pTown->pR, targetpTown, extract);


  if (*extract == 0) return targetpTown;
  if (CHECK_PTR(targetpTown)) {
    char* townName = malloc(sizeof(char)*32);
    if (CHECK_PTR(townName)) exit (200);
    townName = strcpy(townName, pTown->name);
    targetpTown = createAvlTown(townName);
    targetpTown->nPass = pTown->nPass;
    targetpTown->nFirst = pTown->nFirst;
    *extract = *extract - 1;
  } else {
    AvlTown* pNew = NULL;
    char* townName = malloc(sizeof(char)*32);
    if (CHECK_PTR(townName)) exit (200);
    townName = strcpy(townName, pTown->name);
    targetpTown = addAvlTown(targetpTown, townName);
    pNew = isInAvlTown(targetpTown, townName);
    pNew->nPass = pTown->nPass;
    pNew->nFirst = pTown->nFirst;
    *extract = *extract - 1;
  } 

  if (!CHECK_PTR(pTown->pL)) targetpTown = T_Process2(pTown->pL, targetpTown, extract);
  
  return targetpTown;
}


AvlTownsteps* T_Process1(AvlTown* pTown, AvlTownsteps* sortedpTown) {  
  if (pTown != NULL) {
    if (!CHECK_PTR(pTown->pL)) sortedpTown = T_Process1(pTown->pL, sortedpTown);
    if (!CHECK_PTR(pTown->pR)) sortedpTown = T_Process1(pTown->pR, sortedpTown);
    char* townName = malloc(sizeof(char)*32);
    if (CHECK_PTR(townName)) exit (200);
    townName = strcpy(townName, pTown->name);
    AvlTownsteps* pNew = NULL;
    if (CHECK_PTR(sortedpTown)) {
      sortedpTown = createAvlTownsteps(pTown->nPass);
      sortedpTown->nFirst = pTown->nFirst;
      sortedpTown->name = townName;
    } else {
      sortedpTown = addAvlTownsteps(sortedpTown, pTown->nPass); 
      pNew = isInAvlTownsteps(sortedpTown, pTown->nPass);
      // THIS is the workaround for inserting equal nodes to the right.
      // THIS COMPLETELY BREAKS IF WE GET THE SAME TOWN NAME TWICE IN
      // PTOWN. However, if pTown ever has the same town in it twice,
      // something has gone CATASTROPHICALLY wrong.
      if (!CHECK_PTR(pNew->name) && strcmp(pNew->name, townName) != 0) {
        while (!CHECK_PTR(pNew->name)) {
          pNew = isInAvlTownsteps(pNew->pR, pTown->nPass);
        }
      }
      pNew->nFirst = pTown->nFirst;
      pNew->name = townName;
    }
  }
  return sortedpTown;
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
    printf("%ld:%f:%f:%f\n", pRoute->id, pRoute->distTot / pRoute->nSteps, pRoute->distMax, pRoute->distMin);
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