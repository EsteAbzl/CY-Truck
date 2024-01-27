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


int avlHeight(void *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvl(ptr) && !checkRightAvl(ptr)) {
    return 1;
  } else {
    if (checkLeftAvl(ptr)) {
      countL = avlHeight(ptr->pL);
    }
    if (checkRightAvl(ptr)) {
      countR = avlHeight(ptr->pR);
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


void *avlRotationL(void *pTree) {
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


void *avlRotationR(void *pTree) {
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


void *avlRotationRL(void *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlRotationR(pTree->pR);
  return avlRotationL(pTree);
}


void *avlRotationLR(void *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlRotationL(pTree->pL);
  return avlRotationR(pTree);
}


#endif