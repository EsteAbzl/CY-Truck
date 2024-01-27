AvlDriver *createAvlDriver(char *str) {
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
AvlDriver *addAvlDriver(AvlDriver *pTree, char *str) {
  static int h = 0;
  return _addAvlDriver(pTree, str, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8
AvlDriver *_addAvlDriver(AvlDriver *pTree, char *str, int *h) {
  if (pTree == NULL) {
    // If in a leaf, add the node there
    *h = 1;
    return createAvlDriver(str);
  } else if (strcmp(str, pTree->name) < 0) {
    // If the new node's value is lesser, check the left branch
    pTree->pL = _addAvlDriver(pTree->pL, str, h);
    // balance factor needs to be inverted
    *h = -*h;
  } else if (strcmp(str, pTree->name) > 0) {
    // If the new node's value is greater, check the right branch
    pTree->pR = _addAvlDriver(pTree->pR, str, h);
  } else {
    // If the new node's value is equal, abort the insertion,
    // This prevent duplicate entries.
    *h = 0;
    return pTree;
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvl(pTree);
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
AvlDriver *delAvlDriver(AvlDriver *pTree, char *str) {
  static int h = 0;
  return _delAvlDriver(pTree, str, &h);
}


AvlDriver *_delAvlDriver(AvlDriver *pTree, char *str, int *h) {
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
  // Element was found, replace as needed
  else if (!checkLeftAvl(pTree)){
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
    pTree = balanceAvl(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}


AvlDriver *delAvlLargestStr(AvlDriver *pTree, char **str) {
  AvlDriver *tmp;
  if (checkRightAvl(pTree)) {
    delAvlLargestStr(pTree->pR, str);
  } else {
    *str = pTree->name;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}


// DEBUG
void displayInorder(AvlDriver *p) {
  if (p != NULL) {
    displayInorder(p->pL);
    printf("%s", p->name);
    displayInorder(p->pR);
  }
}
