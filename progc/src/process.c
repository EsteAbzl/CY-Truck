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
  
  //
  // PASS 2 : get 10 most visited towns
  // 
  // To prevent previous issues with duplicate nPass values,
  // We're going to avoid making an nPath AVL altogether.
  // This is a bit hacky as using a sequential array to sort is
  // slow, but we should only need to sort an array of size 10
  // Since we'll only compare a value to the smallest of the array
  // to not even compare our input values should we not need to
  // add them to the top 10.
  AvlTown** top10;
  top10 = malloc(10*sizeof(AvlTown*));
  for (int i = 0; i < 10; i++) {
    top10[i] = malloc(sizeof(AvlTown));
    if (CHECK_PTR(top10[i])) exit (200);
    top10[i]->nFirst = 0;
    top10[i]->nPass = 0;
    top10[i]->name = NULL;
  }
  if (!CHECK_PTR(pTown)) T_Process(pTown, top10);

  // 
  // PASS 3 : Alphabetical sorting
  // 
  // Now that we have our top 10 cities, sorting them
  // by alphabetical order is trivial.
  AvlTown* top10pTown = createAvlTown(top10[0]->name);
  top10pTown->nPass = top10[0]->nPass;
  top10pTown->nFirst = top10[0]->nFirst;
  for (int i = 1; i<10; i++) {
    top10pTown = addAvlTown(top10pTown, top10[i]->name);
    AvlTown* pNew = isInAvlTown(top10pTown, top10[i]->name);
    pNew->nPass = top10[i]->nPass;
    pNew->nFirst = top10[i]->nFirst;
  }
  inorderTown(top10pTown);
}


// Very simple code that just gets a top 10 of the values in pTown.
// In theory, this is O(scary), but in practice, it should be fast
// enough since our array is of size 10.
void T_Process(AvlTown* pTown, AvlTown** top10) {
  if (pTown) {
    pTown->nPass = avlIntSize(pTown->pRoutes);

    // If pTown->nPass is large enough to be allowed in the top 10...
    if (pTown->nPass > top10[9]->nPass) {
      // ... Get where it can go to not break the sorting...
      int i = 0;
      while ((pTown->nPass < top10[i]->nPass) && i < 10) {
        i++;
      }

      // "Sliiiiide to the right ! Cha cha real smooth  !""
      for (int j = 8; j >= i; j--) {
        top10[j+1]->name = top10[j]->name;
        top10[j+1]->nPass = top10[j]->nPass;
        top10[j+1]->nFirst = top10[j]->nFirst;
      }
      // Add it to the newly made spot
      top10[i]->nPass = pTown->nPass;
      top10[i]->name = pTown->name;
      top10[i]->nFirst = pTown->nFirst;
    }

    T_Process(pTown->pL, top10);
    T_Process(pTown->pR, top10);
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
    int routeID = pLine->route_ID;
    AvlRoute* pTemp = isInAvlRoute(pRoute, routeID);
    float dist = pLine->distance;
    // Insert the data into the tree
    if (pRoute == NULL) {
      pRoute = createAvlRoute(routeID);
      pRoute->nSteps = 1;
      pRoute->distTot = dist;
      pRoute->distMax = dist;
      pRoute->distMin = dist;
      pRoute->distMaxMin = pRoute->distMax - pRoute->distMin;
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
      pTemp->distMaxMin = pTemp->distMax - pTemp->distMin; 
      pTemp->distTot += dist;
    }
  }
  //
  // PASS 2 : COMPUTE AVERAGES
  //
  AvlRoute** top50;
  top50 = malloc(50*sizeof(AvlRoute*));
  for (int i = 0; i < 50; i++) {
    top50[i] = malloc(sizeof(AvlRoute));
    if (CHECK_PTR(top50[i])) exit (200);
    top50[i]->distMax = 0;
    top50[i]->distMin = 0;
    top50[i]->id = 0;
    top50[i]->distMaxMin = 0;
    top50[i]->distAvg = 0;
  }
  if (!CHECK_PTR(pRoute)) S_Process(pRoute, top50);
  for (int i = 0; i < 50; i++) {
    printf("%i;%f;%f;%f;%i\n", top50[i]->id, top50[i]->distMax, top50[i]->distMin, top50[i]->distAvg, i);
  }
}


// See : T_process
void S_Process(AvlRoute* pRoute, AvlRoute** top50) {
  if (pRoute) {
    pRoute->distAvg = pRoute->distTot / pRoute->nSteps;

    // If pRoute->distMaxMin is large enough to be allowed in the top 50...
    if (pRoute->distMaxMin > top50[49]->distMaxMin) {
      // ... Get where it can go to not break the sorting...
      int i = 0;
      while ((pRoute->distMaxMin < top50[i]->distMaxMin) && i < 50) {
        i++;
      }

      // "Sliiiiide to the right ! Cha cha real smooth  !""
      for (int j = 48; j >= i; j--) {
        // The very thought of doing this makes me feel gross.
        // But eh, it's only size 50. Again, O(scary), but quick enough in practice.
        top50[j+1]->distMax = top50[j]->distMax;
        top50[j+1]->distMin = top50[j]->distMin;
        top50[j+1]->id = top50[j]->id;
        top50[j+1]->distMaxMin = top50[j]->distMaxMin;
        top50[j+1]->distAvg = top50[j]->distAvg;  
      }
      // Add it to the newly made spot
      top50[i]->distMax = pRoute->distMax;
      top50[i]->distMin = pRoute->distMin;
      top50[i]->id = pRoute->id;
      top50[i]->distMaxMin = pRoute->distMaxMin;
      top50[i]->distAvg = pRoute->distAvg; 
    }

    S_Process(pRoute->pL, top50);
    S_Process(pRoute->pR, top50);
  }
}