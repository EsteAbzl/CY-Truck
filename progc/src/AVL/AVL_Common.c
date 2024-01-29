#ifndef _AVLCOMMON_C
#define _AVLCOMMON_C

#include "AVL_Common.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int checkPtr(void *ptr) {
  return ptr == NULL;
}


int checkLeftAvl(void *ptr) {
  return !checkPtr(ptr + OFF_VALUE) && !checkPtr(ptr + OFF_LEFT_CHILD);
}


int checkRightAvl(void *ptr) {
  return !checkPtr(ptr + OFF_VALUE) && !checkPtr(ptr + OFF_RIGHT_CHILD);
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
      countL = avlHeight(ptr + OFF_LEFT_CHILD);
    }
    if (checkRightAvl(ptr)) {
      countR = avlHeight(ptr + OFF_RIGHT_CHILD);
    }
  }
  return MAX(countL, countR) + 1;
}


void *balanceAvl(void *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (*((int*) pTree + OFF_BFACTOR) >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (*((int*) *(*(pTree + OFF_RIGHT_CHILD) + OFF_BFACTOR)) >= 0) {
      return avlRotationL(pTree);
    } else {
      return avlRotationRL(pTree);
    }
  } else if (*((int*) pTree + OFF_BFACTOR) <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (*((int*) *(*(pTree + OFF_LEFT_CHILD) + OFF_BFACTOR)) <= 0) {
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
  int eq_Ptree = *((int*) pTree + OFF_BFACTOR), eq_Pivot = Pivot->bFactor;
  *((int*) pTree + OFF_BFACTOR) -= MAX(eq_Pivot, 0) - 1;
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
  int eq_Ptree = *((int*) pTree + OFF_BFACTOR), eq_Pivot = Pivot->bFactor;
  *((int*) pTree + OFF_BFACTOR) -= MIN(eq_Pivot, 0) + 1;
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