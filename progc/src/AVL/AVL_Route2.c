#include "AVL_Route2.h"

AvlRoute2* createAvlRoute2(float distMaxMin) {
  AvlRoute2 *pNew = malloc(sizeof(AvlRoute2));
  if (CHECK_PTR(pNew)) exit(1);
  pNew->distMaxMin = distMaxMin;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  pNew->distAvg = 0;
  pNew->distMax = 0;
  pNew->distMin = 0;
  pNew->id = 0;
  return pNew;
}


// First function gets called as our main BST adding function.
// This is necessary to set a default value for the balance factor h,
// the alternative being a f_args function, which would be way too
// much effort for the same outcome.
AvlRoute2* addAvlRoute2(AvlRoute2 *pTree, float distMaxMin) {
  static float h = 0;
  return _addAvlRoute2(pTree, distMaxMin, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8

AvlRoute2* _addAvlRoute2(AvlRoute2 *pTree, float distMaxMin, float *h) {
  if (pTree == NULL) {
    // If in a leaf, add the node there
    *h = 1;
    return createAvlRoute2(distMaxMin);
  } else if (distMaxMin > pTree->distMaxMin) {
    pTree->pR = _addAvlRoute2(pTree->pR, distMaxMin, h);
  }else if (distMaxMin < pTree->distMaxMin) {
    // If the new node's value is lesser, check the left branch
    pTree->pL = _addAvlRoute2(pTree->pL, distMaxMin, h);
    // balance factor needs to be inverted
    *h = -*h;
  } else {
    *h = 0;
    return pTree;
  }
  // prfloatf("DEBUG 500\n");
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlRoute2(pTree);
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
AvlRoute2* delAvlRoute2(AvlRoute2 *pTree, char *str) {
  static float h = 0;
  return _delAvlRoute2(pTree, str, &h);
}
*/

AvlRoute2* delAvlRoute2(AvlRoute2 *pTree, float* distMaxMin, float *h) {
  // Element not in tree
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // Recursively search through the BST
  else if (*distMaxMin > pTree->distMaxMin) {
    pTree->pR = delAvlRoute2(pTree->pR, distMaxMin, h);
  } else if (*distMaxMin < pTree->distMaxMin) {
    pTree->pL = delAvlRoute2(pTree->pL, distMaxMin, h);
    *h = -*h;
  }
  // Element found, replace as needed
  else if (!checkLeftAvlRoute2(pTree)){
    AvlRoute2 *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  else {
    pTree->pL = delAvlLargestFloat(pTree->pL, distMaxMin);
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlRoute2(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return pTree;
}


AvlRoute2* delAvlLargestFloat(AvlRoute2 *pTree, float *distMaxMin) {
  AvlRoute2 *tmp;
  if (checkRightAvlRoute2(pTree)) {
    delAvlLargestFloat(pTree->pR, distMaxMin);
  } else {
    *distMaxMin = pTree->distMaxMin;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

AvlRoute2* isInAvlRoute2(AvlRoute2 *pTree, float distMaxMin){
  AvlRoute2* ret = NULL;
  if (pTree == NULL) {
    // Return NULL if not found
    ret = NULL;
  } else if (distMaxMin < pTree->distMaxMin) {
    // Search value lower than current value, go left
    ret = isInAvlRoute2(pTree->pL, distMaxMin);
    // prfloatf("isinavl go left\n");
  } else if (distMaxMin > pTree->distMaxMin) {
    // Search value higher than current value, go right
    ret = isInAvlRoute2(pTree->pR, distMaxMin);
    // prfloatf("isinavl go right\n");
  } else {
    // Return the current node if found
    ret = pTree;
    // prfloatf("isinavl found\n");
  }
  return ret;
}


float checkLeftAvlRoute2(AvlRoute2 *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}


float checkRightAvlRoute2(AvlRoute2 *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


float avlRoute2Height(AvlRoute2 *ptr) { // hauteur
  float countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvlRoute2(ptr) && !checkRightAvlRoute2(ptr)) {
    return 1;
  } else {
    if (checkLeftAvlRoute2(ptr)) {
      countL = avlRoute2Height(ptr->pL);
    }
    if (checkRightAvlRoute2(ptr)) {
      countR = avlRoute2Height(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
}


AvlRoute2 *balanceAvlRoute2(AvlRoute2 *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return avlRoute2RotationL(pTree);
    } else {
      return avlRoute2RotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return avlRoute2RotationR(pTree);
    } else {
      return avlRoute2RotationLR(pTree);
    }
  }
  return pTree;
}


AvlRoute2 *avlRoute2RotationL(AvlRoute2 *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlRoute2 *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  float eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;
  return pTree;
}


AvlRoute2 *avlRoute2RotationR(AvlRoute2 *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlRoute2 *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  float eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;
  return pTree;
}


AvlRoute2 *avlRoute2RotationRL(AvlRoute2 *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlRoute2RotationR(pTree->pR);
  return avlRoute2RotationL(pTree);
}


AvlRoute2 *avlRoute2RotationLR(AvlRoute2 *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlRoute2RotationL(pTree->pL);
  return avlRoute2RotationR(pTree);
}


void inorderRoute2(AvlRoute2 *pTree, int* i){
  if(!CHECK_PTR(pTree)){
    if (*i < 50) {
      inorderRoute2(pTree->pR, i);
      printf("%i;%f;%f;%f;%i\n", pTree->id, pTree->distMax, pTree->distMin, pTree->distAvg, *i);
      *i = *i + 1;
      inorderRoute2(pTree->pL, i);
    }
  }
}