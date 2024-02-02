#include "AVL_Int.h"

AvlInt* createAvlInt(int id) {
  AvlInt *pNew = malloc(sizeof(AvlInt));
  if (CHECK_PTR(pNew)) exit(1);
  pNew->id = id;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  return pNew;
}


// First function gets called as our main BST adding function.
// This is necessary to set a default value for the balance factor h,
// the alternative being a f_args function, which would be way too
// much effort for the same outcome.
AvlInt* addAvlInt(AvlInt *pTree, int id) {
  static int h = 0;
  return _addAvlInt(pTree, id, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8

AvlInt* _addAvlInt(AvlInt *pTree, int id, int *h) {
  if (pTree == NULL) {
    // If in a leaf, add the node there
    *h = 1;
    return createAvlInt(id);
  } else if (id > pTree->id) {
    pTree->pR = _addAvlInt(pTree->pR, id, h);
  }else if (id < pTree->id) {
    // If the new node's value is lesser, check the left branch
    pTree->pL = _addAvlInt(pTree->pL, id, h);
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
    pTree = balanceAvlInt(pTree);
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
AvlInt* delAvlInt(AvlInt *pTree, char *str) {
  static int h = 0;
  return _delAvlInt(pTree, str, &h);
}
*/

AvlInt* delAvlInt(AvlInt *pTree, int* id, int *h) {
  // Element not in tree
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // Recursively search through the BST
  else if (*id > pTree->id) {
    pTree->pR = delAvlInt(pTree->pR, id, h);
  } else if (*id < pTree->id) {
    pTree->pL = delAvlInt(pTree->pL, id, h);
    *h = -*h;
  }
  // Element found, replace as needed
  else if (!checkLeftAvlInt(pTree)){
    AvlInt *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  else {
    pTree->pL = delAvlLargestInt(pTree->pL, id);
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlInt(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return pTree;
}


AvlInt* delAvlLargestInt(AvlInt *pTree, int *id) {
  AvlInt *tmp;
  if (checkRightAvlInt(pTree)) {
    delAvlLargestInt(pTree->pR, id);
  } else {
    *id = pTree->id;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

AvlInt* isInAvlInt(AvlInt *pTree, int id){
  AvlInt* ret = NULL;
  if (pTree == NULL) {
    // Return NULL if not found
    ret = NULL;
  } else if (id < pTree->id) {
    // Search value lower than current value, go left
    ret = isInAvlInt(pTree->pL, id);
    // printf("isinavl go left\n");
  } else if (id > pTree->id) {
    // Search value higher than current value, go right
    ret = isInAvlInt(pTree->pR, id);
    // printf("isinavl go right\n");
  } else {
    // Return the current node if found
    ret = pTree;
    // printf("isinavl found\n");
  }
  return ret;
}


int checkLeftAvlInt(AvlInt *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}


int checkRightAvlInt(AvlInt *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


int avlIntHeight(AvlInt *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvlInt(ptr) && !checkRightAvlInt(ptr)) {
    return 1;
  } else {
    if (checkLeftAvlInt(ptr)) {
      countL = avlIntHeight(ptr->pL);
    }
    if (checkRightAvlInt(ptr)) {
      countR = avlIntHeight(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
}


int avlIntSize(AvlInt *ptr) { // size
  if (ptr == NULL) return 0;
  int i = 1;
  i += avlIntSize(ptr->pL);
  i += avlIntSize(ptr->pR);
  return i;
}


AvlInt *balanceAvlInt(AvlInt *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return avlIntRotationL(pTree);
    } else {
      return avlIntRotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return avlIntRotationR(pTree);
    } else {
      return avlIntRotationLR(pTree);
    }
  }
  return pTree;
}


AvlInt *avlIntRotationL(AvlInt *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlInt *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;
  return pTree;
}


AvlInt *avlIntRotationR(AvlInt *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlInt *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;
  return pTree;
}


AvlInt *avlIntRotationRL(AvlInt *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlIntRotationR(pTree->pR);
  return avlIntRotationL(pTree);
}


AvlInt *avlIntRotationLR(AvlInt *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlIntRotationL(pTree->pL);
  return avlIntRotationR(pTree);
}


void inorderInt(AvlInt *pTree){
  if(!CHECK_PTR(pTree)){
    inorderInt(pTree->pL);
    printf("%d\n", pTree->id);
    inorderInt(pTree->pR);
  }
}

void freeAvlInt(AvlInt *pTree){
  if(!CHECK_PTR(pTree)){
    freeAvlInt(pTree->pL);
    freeAvlInt(pTree->pR);
    if (!CHECK_PTR(pTree)) free(pTree);
  }
}