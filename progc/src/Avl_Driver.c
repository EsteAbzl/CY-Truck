AvlDriver *createAvlDriver(char *str) {
  AvlDriver *pNew = malloc(sizeof(AvlDriver));
  if (pNew == NULL) {
    exit(1);
  }
  pNew->name = str;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  pNew->avlPath = NULL;
  return pNew;
}


int checkPtr(void *ptr) {
  return ptr == NULL;
}


int checkLeftAVL(void *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pL);
}


int checkRightAVL(void *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pR);
}


int bstHeight(void *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAVL(ptr) && !checkRightAVL(ptr)) {
    return 1;
  } else {
    if (checkLeftAVL(ptr)) {
      countL = bstHeight(ptr->pL);
    }
    if (checkRightAVL(ptr)) {
      countR = bstHeight(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
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
    // new node position found
    *h = 1;
    return createAvlDriver(str);
  } else if (strcmp(pTree->name, str) > 0) {
    // look into the left subtree
    pTree->pL = _addAvlDriver(pTree->pL, str, h);
    // balance factor needs to be inverted in this case
    *h = -*h;
  } else if (strcmp(pTree->name, str) < 0) {
    // look into the right subtree
    pTree->pR = _addAvlDriver(pTree->pR, str, h);
  } else {
    // This prevents duplicate values  
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
  else if (strcmp(pTree->name, str) < 0) {
    pTree->pR = _delAvlDriver(pTree->pR, str, h);
  } else if (strcmp(pTree->name, str) > 0) {
    pTree->pL = _delAvlDriver(pTree->pL, str, h);
    *h = -*h;
  }
  // Element was found, replace as needed
  else if (!checkLeftAVL(pTree)){
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


AvlDriver *delAvlLargestStr(AvlDriver *pTree, char **str) {
  AvlDriver *tmp;
  if (checkRightAVL(pTree)) {
    delAvlLargestStr(pTree->pR, str);
  } else {
    *str = pTree->name;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}


AvlDriver *avlRotationL(AvlDriver *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlDriver *Pivot = pTree->pR;

  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor -= MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor =
      MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));

  pTree = Pivot;
  return pTree;
}


AvlDriver *avlRotationR(AvlDriver *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlDriver *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor -= MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor =
      MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));

  pTree = Pivot;
  return pTree;
}


AvlDriver *avlRotationRL(AvlDriver *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlRotationR(pTree->pR);
  return avlRotationL(pTree);
}


AvlDriver *avlRotationLR(AvlDriver *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlRotationL(pTree->pL);
  return avlRotationR(pTree);
}


AvlDriver *balanceAvlDriver(AvlDriver *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return avlRotationL(pTree);
    } else {
      return avlRotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return avlRotationR(pTree);
    } else {
      return avlRotationLR(pTree);
    }
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
