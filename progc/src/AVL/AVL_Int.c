#ifndef _AVLINT_C
#define _AVLINT_C

#include "AVL_Common.h"

AvlInt *createAvlInt(int v) {
  AvlInt *pNew = malloc(sizeof(AvlInt));
  if (checkPtr(pNew)) exit (1);
  pNew->value = v;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  return pNew;
}


// First function gets called as our main BST adding function.
// This is necessary to set a default value for the balance factor h,
// the alternative being a f_args function, which would be way too
// much effort for the same outcome.
AvlInt *addAvlInt(AvlInt *pTree, int elem) {
  static int h = 0;
  return _addAvlInt(pTree, elem, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8
AvlInt *_addAvlInt(AvlInt *p, int v, int *h) {
  if (checkPtr(p)) {
    // If in a leaf, add the new node there.
    *h = 1;
    return createAvlInt(v);
  } else if (v < p->value) {
    // If the new node's value is lesser, check the left branch
    p->pL = _addAvlInt(p->pL, v, h);
    // balance factor needs to be inverted
    *h = -*h;
  } else if (v > p->value) {
    // If the new node's value is greater, check the right branch
    p->pR = _addAvlInt(p->pR, v, h);
  } else {
    // If the new node's value is equal, abort the insertion,
    // This prevent duplicate entries.
    *h = 0;
    return p;
  }
  if (*h != 0) {
    p->bFactor = p->bFactor + *h;
    p = balanceAvlInt(p);
    if (p->bFactor == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return p;
}


// Same Hack
// When I wrote this code, only me and God knew why we had to do
// it that way. Now, days later, only God knows.
// May Richie have mercy on our souls.
AvlInt *delAvlInt(AvlInt *pTree, int elem) {
  static int h = 0;
  return _delAvlInt(pTree, elem, &h);
}


AvlInt *_delAvlInt(AvlInt *pTree, int elem, int *h) {
  // Element not in tree
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // Recursively search through BST
  else if (pTree->value < elem) {
    pTree->pR = _delAvlInt(pTree->pR, elem, h);
  } else if (pTree->value > elem) {
    pTree->pL = _delAvlInt(pTree->pL, elem, h);
    *h = -*h;
  }
  // Element found, replace as needed
  else if (!checkLeftAvlInt(pTree)) {
    AvlInt *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  else {
    pTree->pL = delAvlLargestInt(pTree->pL, &(pTree->value));
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


AvlInt *delAvlLargestInt(AvlInt *pTree, int *elem) {
  AvlInt *tmp;
  if (checkRightAvlInt(pTree)) {
    delAvlLargestInt(pTree->pR, elem);
  } else {
    *elem = pTree->value;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}


int checkLeftAvlInt(AvlInt *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pL);
}


int checkRightAvlInt(AvlInt *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pR);
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
  pTree->bFactor -= MAX(eq_Pivot, 0) - 1;
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
  pTree->bFactor -= MIN(eq_Pivot, 0) + 1;
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


#endif
