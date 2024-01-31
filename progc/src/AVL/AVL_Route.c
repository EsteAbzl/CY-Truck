#ifndef _AVLROUTE_C
#define _AVLROUTE_C

#include "AVL_Common.h"
#include "AVL_Route.h"

AvlRoute* createAvlRoute(long id) {
  AvlRoute *pNew = malloc(sizeof(AvlRoute));
  if (CHECK_PTR(pNew)) exit(1);
  pNew->id = id;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  pNew->distTot = 0;
  pNew->distMax = 0;
  pNew->distMin = 0;
  pNew->nSteps = 0;
  return pNew;
}


// First function gets called as our main BST adding function.
// This is necessary to set a default value for the balance factor h,
// the alternative being a f_args function, which would be way too
// much effort for the same outcome.
AvlRoute* addAvlRoute(AvlRoute *pTree, long id) {
  static int h = 0;
  return _addAvlRoute(pTree, id, &h);
}


// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8

AvlRoute* _addAvlRoute(AvlRoute *pTree, long id, int *h) {
  if (pTree == NULL) {
    // If in a leaf, add the node there
    *h = 1;
    return createAvlRoute(id);
  } else if (id > pTree->id) {
    pTree->pR = _addAvlRoute(pTree->pR, id, h);
  }else if (id < pTree->id) {
    // If the new node's value is lesser, check the left branch
    pTree->pL = _addAvlRoute(pTree->pL, id, h);
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
    pTree = balanceAvlRoute(pTree);
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
AvlRoute* delAvlRoute(AvlRoute *pTree, char *str) {
  static int h = 0;
  return _delAvlRoute(pTree, str, &h);
}
*/

AvlRoute* delAvlRoute(AvlRoute *pTree, long* id, int *h) {
  // Element not in tree
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // Recursively search through the BST
  else if (*id > pTree->id) {
    pTree->pR = delAvlRoute(pTree->pR, id, h);
  } else if (*id < pTree->id) {
    pTree->pL = delAvlRoute(pTree->pL, id, h);
    *h = -*h;
  }
  // Element found, replace as needed
  else if (!checkLeftAvlRoute(pTree)){
    AvlRoute *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  else {
    pTree->pL = delAvlLargestLong(pTree->pL, id);
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlRoute(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return pTree;
}


AvlRoute* delAvlLargestLong(AvlRoute *pTree, long *id) {
  AvlRoute *tmp;
  if (checkRightAvlRoute(pTree)) {
    delAvlLargestLong(pTree->pR, id);
  } else {
    *id = pTree->id;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

AvlRoute* isInAvlRoute(AvlRoute *pTree, long id){
  AvlRoute* ret = NULL;
  if (pTree == NULL) {
    // Return NULL if not found
    ret = NULL;
  } else if (id < pTree->id) {
    // Search value lower than current value, go left
    ret = isInAvlRoute(pTree->pL, id);
    // printf("isinavl go left\n");
  } else if (id > pTree->id) {
    // Search value higher than current value, go right
    ret = isInAvlRoute(pTree->pR, id);
    // printf("isinavl go right\n");
  } else {
    // Return the current node if found
    ret = pTree;
    // printf("isinavl found\n");
  }
  return ret;
}


int checkLeftAvlRoute(AvlRoute *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}


int checkRightAvlRoute(AvlRoute *ptr) {
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


int avlRouteHeight(AvlRoute *ptr) { // hauteur
  int countL = 0, countR = 0;
  if (ptr == NULL) {
    return 0;
  }
  if (!checkLeftAvlRoute(ptr) && !checkRightAvlRoute(ptr)) {
    return 1;
  } else {
    if (checkLeftAvlRoute(ptr)) {
      countL = avlRouteHeight(ptr->pL);
    }
    if (checkRightAvlRoute(ptr)) {
      countR = avlRouteHeight(ptr->pR);
    }
  }
  return MAX(countL, countR) + 1;
}


AvlRoute *balanceAvlRoute(AvlRoute *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->bFactor >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->bFactor >= 0) {
      return avlRouteRotationL(pTree);
    } else {
      return avlRouteRotationRL(pTree);
    }
  } else if (pTree->bFactor <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->bFactor <= 0) {
      return avlRouteRotationR(pTree);
    } else {
      return avlRouteRotationLR(pTree);
    }
  }
  return pTree;
}


AvlRoute *avlRouteRotationL(AvlRoute *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlRoute *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;
  return pTree;
}


AvlRoute *avlRouteRotationR(AvlRoute *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlRoute *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;
  return pTree;
}


AvlRoute *avlRouteRotationRL(AvlRoute *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlRouteRotationR(pTree->pR);
  return avlRouteRotationL(pTree);
}


AvlRoute *avlRouteRotationLR(AvlRoute *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlRouteRotationL(pTree->pL);
  return avlRouteRotationR(pTree);
}


void inorderRoute(AvlRoute *pTree){
  if(!CHECK_PTR(pTree)){
    inorderRoute(pTree->pL);
    printf("%ld, nSteps: %i, distTot: %f\n", pTree->id, pTree->nSteps, pTree->distTot);
    inorderRoute(pTree->pR);
  }
}

#endif
