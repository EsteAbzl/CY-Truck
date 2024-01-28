#ifndef _AVLINT_C
#define _AVLINT_C

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
    p->pL = addAvlInt(p->pL, v, h);
    // balance factor needs to be inverted
    *h = -*h;
  } else if (v > p->value) {
    // If the new node's value is greater, check the right branch
    p->pR = addAvlInt(p->pR, v, h);
  } else {
    // If the new node's value is equal, abort the insertion,
    // This prevent duplicate entries.
    *h = 0;
    return p;
  }
  if (*h != 0) {
    p->bFactor = p->bFactor + *h;
    p = balanceAvl(p);
    if (p->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return p;
}


// Same Hack
// When I wrote this code, only me and God knew why we had to do
// it that way. Now, days later, only God knows.
// May Richie have mercy on our souls.
AvlDriver *delAvlInt(AvlDriver *pTree, char *str) {
  static int h = 0;
  return _delAvlDriver(pTree, str, &h);
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
  else if (!checkLeftAvl(pTree)) {
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
    pTree = equilibrage(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}


AvlInt *delAvlLargestInt(AvlInt *pTree, int *elem) {
  AvlInt *tmp;
  if (AvlRightExist(pTree)) {
    delAvlLargestInt(pTree->pR, elem);
  } else {
    *elem = pTree->value;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}


#endif