#include "AVL_Int.h"

AvlInt* init_AvlInt(){
  AvlInt *pNew = malloc(sizeof(AvlInt));
  if (CHECK_PTR(pNew)) exit(1);

  pNew->h = 0;
  pNew->pRoot = NULL;

  return pNew;
}

NodeAvlInt* create_NodeAvlInt(int id, Route* pRoute){
  NodeAvlInt *pNew = malloc(sizeof(NodeAvlInt));
  if (CHECK_PTR(pNew)) exit(1);

  pNew->value = id;

  pNew->pRoute = pRoute; // Can be set to NULL

  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  
  return pNew;
}

void free_SingularNodeAvlInt(NodeAvlInt* pTree){
  if(pTree){
    if(pTree->pRoute){
      free(pTree->pRoute);
    }

    free(pTree);
  }
}

void free_NodeAvlInt(NodeAvlInt* pTree){
  if(pTree){
    if(pTree->pRoute){
      free(pTree->pRoute);
    }

    free_NodeAvlInt(pTree->pL);
    free_NodeAvlInt(pTree->pR);

    free(pTree);
  }
}

void free_AvlInt(AvlInt* pAvl){
  if(pAvl){
    free_NodeAvlInt(pAvl->pRoot);

    free(pAvl);
  }
}



void add_AvlInt(AvlInt *pAvl, Route* pRoute, int id){
  pAvl->pRoot = add_NodeAvlInt(pAvl->pRoot, id, pRoute, &pAvl->h);
}

// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8

NodeAvlInt* add_NodeAvlInt(NodeAvlInt *pTree, int id, Route* pRoute, int *h) {
  if(pTree == NULL){                // If in a leaf, add the node there
    *h = 1;
    return create_NodeAvlInt(id, pRoute);
  } 
  else if(id > pTree->value){
    pTree->pR = add_NodeAvlInt(pTree->pR, id, pRoute, h);
  }
  else if(id < pTree->value){
    // If the new node's value is lesser, check the left branch
    pTree->pL = add_NodeAvlInt(pTree->pL, id, pRoute, h);
    // balance factor needs to be inverted
    *h = -*h;
  } 
  else{
    // If the new node's value is equal, abort the insertion,
    // This prevent duplicate entries.
    *h = 0;
    return pTree;
  }

  if(*h != 0){
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlRoute(pTree);
    if(pTree->bFactor == 0){
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return pTree;
}



void del_AvlInt(AvlInt *pAvl, int id){
  pAvl->pRoot = del_NodeAvlInt(pAvl->pRoot, &id, &pAvl->h);
}

NodeAvlInt* del_NodeAvlInt(NodeAvlInt *pTree, int *id, int *h){
  if(pTree == NULL){   // Element not in tree
    *h = 1;
    return pTree;
  }
  else if(*id > pTree->value){   // Recursively search through the BST
    pTree->pR = del_NodeAvlInt(pTree->pR, id, h);
  } 
  else if(*id < pTree->value){
    pTree->pL = del_NodeAvlInt(pTree->pL, id, h);
    *h = -*h;
  }

  // Element found, replace as needed
  if(!(pTree->pL)){
    NodeAvlInt *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free_SingularNodeAvlInt(tmp);
    *h = -1;
  }
  else {
    pTree->pL = del_AvlLargestInt(pTree->pL, id);
  }

  if(*h != 0){
    pTree->bFactor = pTree->bFactor + *h;
    pTree = balanceAvlRoute(pTree);
    if(pTree->bFactor == 0){
      *h = 0;
    } 
    else{
      *h = 1;
    }
  }

  return pTree;
}

NodeAvlInt* del_AvlLargestInt(NodeAvlInt *pTree, int *id) {
  NodeAvlInt *tmp;
  if(checkRightAvlRoute(pTree)){
    del_AvlLargestInt(pTree->pR, id);
  } 
  else{
    *id = pTree->value;
    tmp = pTree;
    pTree = pTree->pL;
    free_SingularNodeAvlInt(tmp);
  }

  return pTree;
}


NodeAvlInt* isInAvlInt(NodeAvlInt *pTree, int id){
  NodeAvlInt* ret = NULL;
  if(pTree == NULL){            // Return NULL if not found
    ret = NULL;
  } 
  else if(id < pTree->value) {  // Search value lower than current value, go left
    ret = isInAvlRoute(pTree->pL, id);
  } 
  else if (id > pTree->value) { // Search value higher than current value, go right
    ret = isInAvlRoute(pTree->pR, id);
  } 
  else {                        // Return the current node if found
    ret = pTree;
  }
  return ret;
}


int checkLeftAvlInt(NodeAvlInt *ptr){
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}

int checkRightAvlInt(NodeAvlInt *ptr){
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


NodeAvlInt *balanceAvlInt(NodeAvlInt *pTree){
  if(pTree == NULL){
    return pTree;
  }
  else if(pTree->bFactor >= 2){
    if(pTree->pR == NULL){
      exit(1);
    }

    if(pTree->pR->bFactor >= 0){
      return avlIntRotationL(pTree);
    }
    else{
      return avlIntRotationRL(pTree);
    }
  } 
  else if(pTree->bFactor <= -2){
    if(pTree->pL == NULL){
      exit(1);
    }

    if(pTree->pL->bFactor <= 0){
      return avlIntRotationR(pTree);
    }
    else{
      return avlIntRotationLR(pTree);
    }
  }

  return pTree;
}


NodeAvlInt *avlIntRotationL(NodeAvlInt *pTree){
  if(!checkRightAvlInt(pTree)){
    return 0;
  }

  NodeAvlInt *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;

  return pTree;
}

NodeAvlInt *avlIntRotationR(NodeAvlInt *pTree){
  if(!checkLeftAvlInt(pTree)){
    return 0;
  }

  NodeAvlInt *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;

  return pTree;
}

NodeAvlInt *avlIntRotationRL(NodeAvlInt *pTree){
  if(CHECK_PTR(pTree)){
    return 0;
  }

  pTree->pR = avlIntRotationR(pTree->pR);
  return avlIntRotationL(pTree);
}

NodeAvlInt *avlIntRotationLR(NodeAvlInt *pTree){
  if(CHECK_PTR(pTree)){
    return 0;
  }

  pTree->pL = avlIntRotationL(pTree->pL);
  return avlIntRotationR(pTree);
}


void inorderInt(NodeAvlInt *pTree){
  if(!CHECK_PTR(pTree)){
    inorderInt(pTree->pL);
    printf("%d, nSteps: %i, distTot: %f\n", pTree->pRoute->id, 
                                            pTree->pRoute->nSteps,
                                            pTree->pRoute->distTot);
    inorderInt(pTree->pR);
  }
}