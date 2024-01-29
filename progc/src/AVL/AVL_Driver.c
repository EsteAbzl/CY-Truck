#ifndef _AVLDRIVER_C
#define _AVLDRIVER_C

#include "AVL_Common.h"

AvlDriver* createAvlDriver(char *str) {
  AvlDriver *pNew = malloc(sizeof(AvlDriver));
  if (checkPtr(pNew)) exit(1);
  pNew->name = str;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  pNew->AvlPath = NULL;
  return pNew;
}


// First function gets called as our main BST adding function.
// This is necessary to set a default value for the balance factor h,
// the alternative being a f_args function, which would be way too
// much effort for the same outcome.
AvlDriver* addAvlDriver(AvlDriver *pTree, char *str) {
  static int h = 0;
  return _addAvlDriver(pTree, str, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8
AvlDriver* _addAvlDriver(AvlDriver *pTree, char *str, int *h) {
  if (pTree == NULL) {
    // If in a leaf, add the node there
    *h = 1;
    return createAvlDriver(str);
  } else if (strcmp(str, pTree->name) < 0) {
    // If the new node's value is lesser, check the left branch
    pTree->pL = _addAvlDriver(pTree->pL, str, h);
    // balance factor needs to be inverted
    *h = -*h;
    _addAvlDriver(pTree->pR, str, h);
  } else {
    // If the new node's value is equal, abort the insertion,
    // This prevent duplicate entries.
    *h = 0;
    return pTree;
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlDriver(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}


// Same Hack
// When I wrote this code, only me and God knew why we had to do
// it that way. Now, days later, only God knows.
// May Richie have mercy on our souls.
AvlDriver* delAvlDriver(AvlDriver *pTree, char *str) {
  static int h = 0;
  return _delAvlDriver(pTree, str, &h);
}


AvlDriver* _delAvlDriver(AvlDriver *pTree, char *str, int *h) {
  // Element not in tree
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // Recursively search through the BST
  else if (strcmp(str, pTree->name) > 0) {
    pTree->pR = _delAvlDriver(pTree->pR, str, h);
  } else if (strcmp(str, pTree->name) < 0) {
    pTree->pL = _delAvlDriver(pTree->pL, str, h);
    *h = -*h;
  }
  // Element found, replace as needed
  else if (!checkLeftAvlDriver(pTree)){
    AvlDriver *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  else {
    pTree->pL = delAvlLargestStr(pTree->pL, &(pTree->name));
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlDriver(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}


AvlDriver* delAvlLargestStr(AvlDriver *pTree, char **str) {
  AvlDriver *tmp;
  if (checkRightAvlDriver(pTree)) {
    delAvlLargestStr(pTree->pR, str);
  } else {
    *str = pTree->name;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

AvlDriver* isInAvlDriver(AvlDriver *pTree, char *str){
  AvlDriver* ret = NULL;
  if (pTree == NULL) {
    // Return NULL if not found
    ret = NULL;
  } else if (strcmp(str, pTree->name) < 0) {
    // Search value lower than current value, go left
    ret = isInAvlDriver(pTree->pL, str);
  } else if (strcmp(str, pTree->name) > 0) {
    // Search value higher than current value, go right
    ret = isInAvlDriver(pTree->pR, str);
  } else if (strcmp(str, pTree->name) == 0) {
    // Return the current node if found
    ret = pTree;
  }
  return ret;
}


int checkLeftAvlDriver(AvlDriver *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pL);
}


int checkRightAvlDriver(AvlDriver *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pR);
}


int avlDriverHeight(AvlDriver *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvlDriver(ptr) && !checkRightAvlDriver(ptr)) {
    return 1;
  } else {
    if (checkLeftAvlDriver(ptr)) {
      countL = avlDriverHeight(ptr->pL);
    }
    if (checkRightAvlDriver(ptr)) {
      countR = avlDriverHeight(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
}


AvlDriver *balanceAvlDriver(AvlDriver *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return avlDriverRotationL(pTree);
    } else {
      return avlDriverRotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return avlDriverRotationR(pTree);
    } else {
      return avlDriverRotationLR(pTree);
    }
  }
  return pTree;
}


AvlDriver *avlDriverRotationL(AvlDriver *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlDriver *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor -= MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;
  return pTree;
}


AvlDriver *avlDriverRotationR(AvlDriver *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlDriver *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor -= MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;
  return pTree;
}


AvlDriver *avlDriverRotationRL(AvlDriver *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlDriverRotationR(pTree->pR);
  return avlDriverRotationL(pTree);
}


AvlDriver *avlDriverRotationLR(AvlDriver *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlDriverRotationL(pTree->pL);
  return avlDriverRotationR(pTree);
}


#endif

AvlDriver * pickmin_AvlDriver(AvlDriver *pTree){
  AvlDriver * min, * node;
  int content = 0;
  FIFO * file = malloc(sizeof(FIFO));
  if(file == NULL){
     exit(5);
  }
  min = pTree;
  while(!checkptr(pDriver)){
    file = insertFIFO(pDriver);
    while(!checkptr(file)){
      node = suprFIFO(file);
      NodeShow(node);
      if(TreeLeftExist(node)){
        file=insertFIFO(file,node->pL);
      }
      if(TreeRightExist(node)){
        file=insertFIFO(file,node->pR);
      }
      if(min->totalDist<node->totalDist){
        min = node;
      }
    }
  }
  return min;
}
