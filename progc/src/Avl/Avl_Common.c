#ifndef _AVLCOMMON_C
#define _AVLCOMMON_C

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int checkPtr(void *ptr) {
  return ptr == NULL;
}


int checkLeftAvl(void *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pL);
}


int checkRightAvl(void *ptr) {
  return !checkPtr(ptr) && !checkPtr(ptr->pR);
}


int AvlHeight(void *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvl(ptr) && !checkRightAvl(ptr)) {
    return 1;
  } else {
    if (checkLeftAvl(ptr)) {
      countL = AvlHeight(ptr->pL);
    }
    if (checkRightAvl(ptr)) {
      countR = AvlHeight(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
}


void *balanceAvl(void *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return AvlRotationL(pTree);
    } else {
      return AvlRotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return AvlRotationR(pTree);
    } else {
      return AvlRotationLR(pTree);
    }
  }
  return pTree;
}


void *AvlRotationL(void *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  void *Pivot = pTree->pR;

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


void *AvlRotationR(void *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  void *Pivot = pTree->pL;
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


void *AvlRotationRL(void *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = AvlRotationR(pTree->pR);
  return AvlRotationL(pTree);
}


void *AvlRotationLR(void *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = AvlRotationL(pTree->pL);
  return AvlRotationR(pTree);
}


#endif