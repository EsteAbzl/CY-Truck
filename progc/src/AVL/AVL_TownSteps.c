#include "AVL_TownSteps.h"

AvlTownsteps* createAvlTownsteps(int val) {
  AvlTownsteps *pNew = malloc(sizeof(AvlTownsteps));
  if (CHECK_PTR(pNew)) exit(1);
  pNew->name = NULL;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  pNew->nPass = val;
  pNew->nFirst = 0;
  //printf("DEBUG %s DANS CREATEAVLDRIVER\n", pNew->name);
  return pNew;
}


// First function gets called as our main BST adding function.
// This is necessary to set a default value for the balance factor h,
// the alternative being a f_args function, which would be way too
// much effort for the same outcome.
AvlTownsteps* addAvlTownsteps(AvlTownsteps *pTree, int val) {
  static int h = 0;
  return _addAvlTownsteps(pTree, val, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8

AvlTownsteps* _addAvlTownsteps(AvlTownsteps *pTree, int val, int *h) {
  if (pTree == NULL) {
    // If in a leaf, add the node there
    *h = 1;
    return createAvlTownsteps(val);
  } else if (val > pTree->nPass) {
    pTree->pR = _addAvlTownsteps(pTree->pR, val, h);
  } else if (val < pTree->nPass) {
    // If the new node's value is lesser, check the left branch
    pTree->pL = _addAvlTownsteps(pTree->pL, val, h);
    // balance factor needs to be inverted
    *h = -*h;
  } else {
    *h = 0;
    return pTree;
  }
  // printf("DEBUG 500\n");
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlTownsteps(pTree);
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
AvlTownsteps* delAvlTownsteps(AvlTownsteps *pTree, char *str) {
  static int h = 0;
  return _delAvlTownsteps(pTree, str, &h);
}
*/

AvlTownsteps* delAvlTownsteps(AvlTownsteps *pTree, int val, int *h) {
  // Element not in tree
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // Recursively search through the BST
  else if (val > pTree->nPass) {
    pTree->pR = delAvlTownsteps(pTree->pR, val, h);
  } else if (val < pTree->nPass) {
    pTree->pL = delAvlTownsteps(pTree->pL, val, h);
    *h = -*h;
  }
  // Element found, replace as needed
  else if (!checkLeftAvlTownsteps(pTree)){
    AvlTownsteps *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  else {
    pTree->pL = delAvlLargestPass(pTree->pL, &(pTree->nFirst));
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlTownsteps(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return pTree;
}


AvlTownsteps* delAvlLargestPass(AvlTownsteps *pTree, int *val) {
  AvlTownsteps *tmp;
  if (checkRightAvlTownsteps(pTree)) {
    delAvlLargestPass(pTree->pR, val);
  } else {
    *val = pTree->nPass;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}


AvlTownsteps* isInAvlTownsteps(AvlTownsteps *pTree, int val){
  AvlTownsteps* ret = NULL;
  if (pTree == NULL) {
    // Return NULL if not found
    // printf("isinavl null\n");
    ret = NULL;
    // int i = strcmp("test", "test");
    // printf("strcmp retourne %i", i);
  } else if (val < pTree->nPass) {
    // Search value lower than current value, go left
    ret = isInAvlTownsteps(pTree->pL, val);
    // printf("isinavl go left\n");
  } else if (val > pTree->nPass) {
    // Search value higher than current value, go right
    ret = isInAvlTownsteps(pTree->pR, val);
    // printf("isinavl go right\n");
  } else {
    // Return the current node if found
    ret = pTree;
    // printf("isinavl found\n");
  }
  return ret;
}


int checkLeftAvlTownsteps(AvlTownsteps *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}


int checkRightAvlTownsteps(AvlTownsteps *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


int avlTownstepsHeight(AvlTownsteps *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvlTownsteps(ptr) && !checkRightAvlTownsteps(ptr)) {
    return 1;
  } else {
    if (checkLeftAvlTownsteps(ptr)) {
      countL = avlTownstepsHeight(ptr->pL);
    }
    if (checkRightAvlTownsteps(ptr)) {
      countR = avlTownstepsHeight(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
}

int avlTownstepsNodeCount(AvlTownsteps *ptr) {
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvlTownsteps(ptr) && !checkRightAvlTownsteps(ptr)) {
    return 1;
  } else {
    if (checkLeftAvlTownsteps(ptr)) {
      countL = avlTownstepsNodeCount(ptr->pL);
    }
    if (checkRightAvlTownsteps(ptr)) {
      countR = avlTownstepsNodeCount(ptr->pR);
    }
  }
  return countL + countR + 1;
}

AvlTownsteps *balanceAvlTownsteps(AvlTownsteps *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return avlTownstepsRotationL(pTree);
    } else {
      return avlTownstepsRotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return avlTownstepsRotationR(pTree);
    } else {
      return avlTownstepsRotationLR(pTree);
    }
  }
  return pTree;
}


AvlTownsteps *avlTownstepsRotationL(AvlTownsteps *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlTownsteps *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;
  return pTree;
}


AvlTownsteps *avlTownstepsRotationR(AvlTownsteps *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlTownsteps *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;
  return pTree;
}


AvlTownsteps *avlTownstepsRotationRL(AvlTownsteps *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlTownstepsRotationR(pTree->pR);
  return avlTownstepsRotationL(pTree);
}


AvlTownsteps *avlTownstepsRotationLR(AvlTownsteps *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlTownstepsRotationL(pTree->pL);
  return avlTownstepsRotationR(pTree);
}
