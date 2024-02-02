#include "AVL_Town.h"

AvlTown* createAvlTown(char *str) {
  AvlTown *pNew = malloc(sizeof(AvlTown));
  if (CHECK_PTR(pNew)) exit(1);
  pNew->name = str;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  pNew->pDrivers = NULL;
  pNew->nFirst = 0;
  pNew->pRoutes = NULL;
  return pNew;
}


// First function gets called as our main BST adding function.
// This is necessary to set a default value for the balance factor h,
// the alternative being a f_args function, which would be way too
// much effort for the same outcome.
AvlTown* addAvlTown(AvlTown *pTree, char *str) {
  static int h = 0;
  return _addAvlTown(pTree, str, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8

AvlTown* _addAvlTown(AvlTown *pTree, char *str, int *h) {
  if (pTree == NULL) {
    // If in a leaf, add the node there
    *h = 1;
    return createAvlTown(str);
  } else if (strcmp(str, pTree->name) > 0) {
    pTree->pR = _addAvlTown(pTree->pR, str, h);
  }else if (strcmp(str, pTree->name) < 0) {
    // If the new node's value is lesser, check the left branch
    pTree->pL = _addAvlTown(pTree->pL, str, h);
    // balance factor needs to be inverted
    *h = -*h;
  } else {
    // If the new node's value is equal, abort the insertion,
    // This prevent duplicate entries.
    *h = 0;
    return pTree;
  }
  // printf("DEBUG 500\n");
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlTown(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return pTree;
}

/*
// Same Hack
// When I wrote this code, only me and God knew why we had to do
// it that way. Now, days later, only God knows.
// May Richie have mercy on our souls.
AvlTown* delAvlTown(AvlTown *pTree, char *str) {
  static int h = 0;
  return _delAvlTown(pTree, str, &h);
}
*/

AvlTown* delAvlTown(AvlTown *pTree, char *str, int *h) {
  // Element not in tree
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // Recursively search through the BST
  else if (strcmp(str, pTree->name) > 0) {
    pTree->pR = delAvlTown(pTree->pR, str, h);
  } else if (strcmp(str, pTree->name) < 0) {
    pTree->pL = delAvlTown(pTree->pL, str, h);
    *h = -*h;
  }
  // Element found, replace as needed
  else if (!checkLeftAvlTown(pTree)){
    AvlTown *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  else {
    pTree->pL = delAvlTownLargestStr(pTree->pL, &(pTree->name));
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlTown(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return pTree;
}


AvlTown* delAvlTownLargestStr(AvlTown *pTree, char **str) {
  AvlTown *tmp;
  if (checkRightAvlTown(pTree)) {
    delAvlTownLargestStr(pTree->pR, str);
  } else {
    *str = pTree->name;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

AvlTown* isInAvlTown(AvlTown *pTree, char *str){
  AvlTown* ret = NULL;
  if (pTree == NULL) {
    // Return NULL if not found
    // printf("isinavl null\n");
    ret = NULL;
    // int i = strcmp("test", "test");
    // printf("strcmp retourne %i", i);
  } else if (strcmp(str, pTree->name) < 0) {
    // Search value lower than current value, go left
    ret = isInAvlTown(pTree->pL, str);
    // printf("isinavl go left\n");
  } else if (strcmp(str, pTree->name) > 0) {
    // Search value higher than current value, go right
    ret = isInAvlTown(pTree->pR, str);
    // printf("isinavl go right\n");
  } else {
    // Return the current node if found
    ret = pTree;
    // printf("isinavl found\n");
  }
  return ret;
}


int checkLeftAvlTown(AvlTown *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}


int checkRightAvlTown(AvlTown *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


int avlTownHeight(AvlTown *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvlTown(ptr) && !checkRightAvlTown(ptr)) {
    return 1;
  } else {
    if (checkLeftAvlTown(ptr)) {
      countL = avlTownHeight(ptr->pL);
    }
    if (checkRightAvlTown(ptr)) {
      countR = avlTownHeight(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
}


AvlTown *balanceAvlTown(AvlTown *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return avlTownRotationL(pTree);
    } else {
      return avlTownRotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return avlTownRotationR(pTree);
    } else {
      return avlTownRotationLR(pTree);
    }
  }
  return pTree;
}


AvlTown *avlTownRotationL(AvlTown *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlTown *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;
  return pTree;
}


AvlTown *avlTownRotationR(AvlTown *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlTown *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;
  return pTree;
}


AvlTown *avlTownRotationRL(AvlTown *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlTownRotationR(pTree->pR);
  return avlTownRotationL(pTree);
}


AvlTown *avlTownRotationLR(AvlTown *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlTownRotationL(pTree->pL);
  return avlTownRotationR(pTree);
}


void inorderTown(AvlTown *pTree){
  if(!CHECK_PTR(pTree)){
    inorderTown(pTree->pL);
    printf("%s;%i;%i\n",pTree->name, pTree->nPass, pTree->nFirst);
    inorderTown(pTree->pR);
  }
}