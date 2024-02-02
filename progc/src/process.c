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



// T process start !
void T_Init(FILE* fData){
  // Just setting up the necessary pointers.
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

    // read TOWN A
    char* townName = malloc(sizeof(char)*50);
    if (CHECK_PTR(townName)) exit (220);
    townName = strcpy(townName, pLine->town_A);
    AvlTown* pNew = NULL;

    // check if the town is logged
    AvlTown* pTemp = isInAvlTown(pTown, townName);
    if (pTown == NULL) {
      // case 1 : the AVL isn't initialized, so make it
      pTown = createAvlTown(townName);
      pTown->pRoutes = createAvlInt(pLine->route_ID);
      // if first step, add a nFirst
      if (pLine->step_ID == 1) pTown->nFirst++;
    } else if (pTemp == NULL) {
      // case 2 : the town isn't logged in the avl, so add it
      pTown = addAvlTown(pTown, townName);
      pNew = isInAvlTown(pTown, townName);
      pNew->pRoutes = createAvlInt(pLine->route_ID);
      // if first step, add a nFirst
      if (pLine->step_ID == 1) pNew->nFirst++;
    } else {
      // case 3 : the town is logged in the avl, so append another pass
      pTemp->pRoutes = addAvlInt(pTemp->pRoutes, pLine->route_ID);
      // if first step, add a nFirst
      if (pLine->step_ID == 1) {
        pTemp->nFirst++;
      }
    }
    // read TOWN B
    townName = malloc(sizeof(char)*50);
    if (CHECK_PTR(townName)) exit (220);
    townName = strcpy(townName, pLine->town_B);
    pNew = NULL;

    // check if the town is logged
    pTemp = isInAvlTown(pTown, townName);
    if (pTown == NULL) {
      // case 1 : the AVL isn't initialized, so make it
      pTown = createAvlTown(townName);
      pTown->pRoutes = createAvlInt(pLine->route_ID);
    } else if (pTemp == NULL) {
      // case 2 : the town isn't logged in the avl, so add it
      pTown = addAvlTown(pTown, townName);
      pNew = isInAvlTown(pTown, townName);
      pNew->pRoutes = createAvlInt(pLine->route_ID);
    } else {
      // case 3 : the town is logged in the avl, so append another pass
      pTemp->pRoutes = addAvlInt(pTemp->pRoutes, pLine->route_ID);
    }
  }
  inorderTown(pTown);
  return;
  AvlTown** top10;
  top10 = malloc(10*sizeof(AvlTown*));
  for (int i = 0; i < 10; i++) {
    top10[i] = malloc(sizeof(AvlTown));
    if (CHECK_PTR(top10[i])) exit (200);
    top10[i]->nFirst = 0;
    top10[i]->nPass = 0;
    top10[i]->name = NULL;
  }
  if (!CHECK_PTR(pTown)) T_Process1(pTown, top10);

  for (int i = 0; i < 10; i++) {
    printf("%s, %i, %i\n", top10[i]->name, top10[i]->nPass, top10[i]->nFirst);
  }
  return;
  // Put our top10 in an AVL sorted by town name to sort the result when printing
  AvlTown* top10pTown = createAvlTown(top10[0]->name);
  top10pTown->nPass = top10[0]->nPass;
  top10pTown->nFirst = top10[0]->nFirst;
  for (int i = 1; i<10; i++) {
    top10pTown = addAvlTown(top10pTown, top10[i]->name);
    top10pTown->nPass = top10[0]->nPass;
    top10pTown->nFirst = top10[0]->nFirst;
  }
  inorderTown(top10pTown);
}


// Very simple code that just gets a top 10 of the values in pTown.
void T_Process1(AvlTown* pTown, AvlTown** top10){
  if(pTown){
    pTown->nPass = avlIntSize(pTown->pRoutes); 

    if(pTown->nPass > top10[9]->nPass){
      int i = 0;
      while((pTown->nPass < top10[i]->nPass) && i<10){
        i++;
      }
    
      for(int j = i+1; j < 9; j++) {
        top10[j]->nFirst = top10[j-1]->nFirst;
        top10[j]->nPass = top10[j-1]->nPass;
        top10[j]->name = top10[j-1]->name;
      }
      top10[i]->nPass = pTown->nPass;
      top10[i]->name = pTown->name;
      top10[i]->nFirst = pTown->nFirst;
    }

    T_Process1(pTown->pL, top10);
    T_Process1(pTown->pR, top10);
  }
}

// VESTIGIAL !
// This was the code for the 1.0.0 version of T2. In fact, it works ! It's not sorted,
// but the AVL is indeed filled with every unique driver that went through a town as well
// as the right ammount of passes !

// We thought that we'd keep it in case we felt like working on this version of the assignment.
// It was an, in my opinion, much more fun and interesting challenge mixing different data structures
// than just asking us to do THREE AVLs, two of which are just sorting...
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

// Also vestigial...
void T2_Process(AvlTown* pTown) {
  if (pTown != NULL) {
    T2_Process(pTown->pL);
    printf("%s;%i;%i\n", pTown->name, pTown->nPass, avlDriverNodeCount(pTown->pDrivers));
    T2_Process(pTown->pR);
  }
}


// S works pretty much the exact same way than T does, with a few data types of
// difference. Same thing, put the data in a tree, process it, put it in another to
// sort the processed data, return it, print it, you know the drill.
// If this is unclear in how it works, check the explainations of T, this is just T
// but simpler in execution.
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
      if (pTemp->distMin > dist) pTemp->distMin = dist;
      if (pTemp->distMax < dist) pTemp->distMax = dist;
      pTemp->distTot += dist;
    }
  }
  //
  // PASS 2 : COMPUTE AVERAGES AND PRINT
  //
  AvlRoute2* sortedpRoute = NULL;
  sortedpRoute = S_Process(pRoute, sortedpRoute);
  int* i = malloc(sizeof(int));
  if (CHECK_PTR(i)) exit (200);
  *i = 0;
  inorderRoute2(sortedpRoute, i);
}

AvlRoute2* S_Process(AvlRoute* pRoute, AvlRoute2* sortedpRoute) {
  if (pRoute != NULL) {
    S_Process(pRoute->pL, sortedpRoute);
    AvlRoute2* pNew = NULL;
    int routeID = pRoute->id;
    float distMaxMin = pRoute->distMax - pRoute->distMin;
    float distAvg = pRoute->distTot / pRoute->nSteps;
    // Insert the data into the tree
    if (sortedpRoute == NULL) {
      sortedpRoute = createAvlRoute2(distMaxMin);
      sortedpRoute->id = routeID;
      sortedpRoute->distAvg = distAvg;
      sortedpRoute->distMax = pRoute->distMax;
      sortedpRoute->distMin = pRoute->distMin;
    } else {
      // This suffers from the SAME BUG as the other AVLs.
      // We really need to fix this...
      sortedpRoute = addAvlRoute2(sortedpRoute, distMaxMin);
      pNew = isInAvlRoute2(sortedpRoute, distMaxMin);
      
      pNew->distAvg = distAvg;
      pNew->distMax = pRoute->distMax;
      pNew->distMin = pRoute->distMin;
      pNew->id = routeID;
    }

    S_Process(pRoute->pR, sortedpRoute);
  }
  return sortedpRoute;
}