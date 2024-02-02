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
  // The idea here is simple, we just do a while loop for every line of data in our
  // data.csv file.
  // While the algorithm itself is sequencial, the reasoning behind it is recursive :
  // We want to first log the first town of the first step in a route. To do this,
  // we log the first town, add a pass to it and add to it one start. Then, we process 
  // the step's second town.
  // Now, if we're not on the first step of a route, we only process the second town.
  // This means that we effecitvely turn a path of A->B, B->C, C->D into one linear
  // path of A->B->C->D. By recursion, the last town will have its last town logged,
  // and we went through the whole dataset !
  // Of course, if we see that a step's first and second town are the same, we don't
  // add a pass to it.
  while (readLine(fData, pLine)) {
    // read the current line
    char* townName = malloc(sizeof(char)*50);
    if (CHECK_PTR(townName)) exit (220);
    townName = strcpy(townName, pLine->town_B);
    AvlTown* pNew = NULL;

    // check if the town is logged
    AvlTown* pTemp = isInAvlTown(pTown, townName);
    if (pTown == NULL) {
      // case 1 : the AVL isn't initialized, so make it
      pTown = createAvlTown(townName);
      pTown->nPass++;
    } else if (pTemp == NULL) {
      // case 2 : the town isn't logged in the avl, so add it
      pTown = addAvlTown(pTown, townName);
      pNew = isInAvlTown(pTown, townName);
      pNew->nPass++;
    } else {
      // case 3 : the town is logged in the avl, so append another pass
      pTemp->nPass++;
    }
    // I've unfortunately not found a more elegant way to mix the above code
    // and this one that just re-runs it for the first town of a step.
    // Oh well. It works.
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
        // case 3 : the town is logged
        pTemp->nPass++;
        pTemp->nFirst++;
      }
    }
  }

  //
  // PASS 2 : Sort the data by the most visited towns
  //
  // This is just a sorting AVL step, no need for big fancy explainations.
  // Our first AVL worked with the town's name as the search key, we just
  // put all the data in an AVL that will use the number of passes as 
  // the key so we can sort them by most visited. 
  AvlTownsteps* sortedpTown = NULL;
  sortedpTown = T_Process1(pTown, sortedpTown);
  if (CHECK_PTR(sortedpTown)) exit (69);
  //
  // PASS 3 : Now, sort the ten most visited towns alphabetically.
  //
  // Now that we sorted the data by the most visited towns, we re-sort it
  // in a string-based AVL again. We got all of the most visited towns,
  // but we want to have them outputed in alphabetical order, so string
  // AVL it is !
  int extract = 10;
  AvlTown* top10pTown = NULL;
  // This just returns a tree of extract nodes. Nothing too fancy.
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
      // TODO TODO TODO TODO TODO TODO TODO TODO
      //    FIX AVLS WITH DUPLICATE VALUES !!!
      // TODO TODO TODO TODO TODO TODO TODO TODO
      //if (!CHECK_PTR(pNew->name) && strcmp(pNew->name, townName) != 0) {
      //  while (!CHECK_PTR(pNew->name)) {
      //    pNew = isInAvlTownsteps(pNew->pR, pTown->nPass);
      //  }
      //}
      pNew->nFirst = pTown->nFirst;
      pNew->name = townName;
    }
  }
  return sortedpTown;
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