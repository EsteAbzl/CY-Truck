#include "AVL_Char.h"

AvlChar* init_AvlChar(){
  AvlChar *pNew = malloc(sizeof(AvlChar));
  if (CHECK_PTR(pNew)) exit(1);

  pNew->h = 0;
  pNew->pRoot = NULL;

  return pNew;
}

NodeAvlChar* create_NodeAvlChar(int id, Route* pRoute){
  NodeAvlChar *pNew = malloc(sizeof(NodeAvlChar));
  if (CHECK_PTR(pNew)) exit(1);

  pNew->value = id;

  pNew->pRoute = pRoute; // Can be set to NULL

  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  
  return pNew;
}

void free_SingularNodeAvlChar(NodeAvlChar* pTree){
  if(pTree){
    if(pTree->pRoute){
      free(pTree->pRoute);
    }

    free(pTree);
  }
}

void free_NodeAvlChar(NodeAvlChar* pTree){
  if(pTree){
    if(pTree->pRoute){
      free(pTree->pRoute);
    }

    free_NodeAvlChar(pTree->pL);
    free_NodeAvlChar(pTree->pR);

    free(pTree);
  }
}

void free_AvlChar(AvlChar* pAvl){
  if(pAvl){
    free_NodeAvlChar(pAvl->pRoot);

    free(pAvl);
  }
}



void add_AvlChar(AvlChar *pAvl, Route* pRoute, int id){
  pAvl->pRoot = add_NodeAvlChar(pAvl->pRoot, id, pRoute, &pAvl->h);
}

// It's a bit hacky, but as they say...
// https://www.youtube.com/watch?v=YPN0qhSyWy8

NodeAvlChar* add_NodeAvlChar(NodeAvlChar *pTree, int id, Route* pRoute, int *h) {
  if(pTree == NULL){                // If in a leaf, add the node there
    *h = 1;
    return create_NodeAvlChar(id, pRoute);
  } 
  else if(id > pTree->value){
    pTree->pR = add_NodeAvlChar(pTree->pR, id, pRoute, h);
  }
  else if(id < pTree->value){
    // If the new node's value is lesser, check the left branch
    pTree->pL = add_NodeAvlChar(pTree->pL, id, pRoute, h);
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



void del_AvlChar(AvlChar *pAvl, int id){
  pAvl->pRoot = del_NodeAvlChar(pAvl->pRoot, &id, &pAvl->h);
}

NodeAvlChar* del_NodeAvlChar(NodeAvlChar *pTree, int *id, int *h){
  if(pTree == NULL){   // Element not in tree
    *h = 1;
    return pTree;
  }
  else if(*id > pTree->value){   // Recursively search through the BST
    pTree->pR = del_NodeAvlChar(pTree->pR, id, h);
  } 
  else if(*id < pTree->value){
    pTree->pL = del_NodeAvlChar(pTree->pL, id, h);
    *h = -*h;
  }

  // Element found, replace as needed
  if(!(pTree->pL)){
    NodeAvlChar *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free_SingularNodeAvlChar(tmp);
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

NodeAvlChar* del_AvlLargestInt(NodeAvlChar *pTree, int *id) {
  NodeAvlChar *tmp;
  if(checkRightAvlRoute(pTree)){
    del_AvlLargestInt(pTree->pR, id);
  } 
  else{
    *id = pTree->value;
    tmp = pTree;
    pTree = pTree->pL;
    free_SingularNodeAvlChar(tmp);
  }

  return pTree;
}


NodeAvlChar* isInAvlChar(NodeAvlChar *pTree, int id){
  NodeAvlChar* ret = NULL;
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


int checkLeftAvlChar(NodeAvlChar *ptr){
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}

int checkRightAvlChar(NodeAvlChar *ptr){
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


NodeAvlChar *balanceAvlChar(NodeAvlChar *pTree){
  if(pTree == NULL){
    return pTree;
  }
  else if(pTree->bFactor >= 2){
    if(pTree->pR == NULL){
      exit(1);
    }

    if(pTree->pR->bFactor >= 0){
      return AvlCharRotationL(pTree);
    }
    else{
      return AvlCharRotationRL(pTree);
    }
  } 
  else if(pTree->bFactor <= -2){
    if(pTree->pL == NULL){
      exit(1);
    }

    if(pTree->pL->bFactor <= 0){
      return AvlCharRotationR(pTree);
    }
    else{
      return AvlCharRotationLR(pTree);
    }
  }

  return pTree;
}


NodeAvlChar *AvlCharRotationL(NodeAvlChar *pTree){
  if(!checkRightAvlChar(pTree)){
    return 0;
  }

  NodeAvlChar *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;

  return pTree;
}

NodeAvlChar *AvlCharRotationR(NodeAvlChar *pTree){
  if(!checkLeftAvlChar(pTree)){
    return 0;
  }

  NodeAvlChar *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;

  return pTree;
}

NodeAvlChar *AvlCharRotationRL(NodeAvlChar *pTree){
  if(CHECK_PTR(pTree)){
    return 0;
  }

  pTree->pR = AvlCharRotationR(pTree->pR);
  return AvlCharRotationL(pTree);
}

NodeAvlChar *AvlCharRotationLR(NodeAvlChar *pTree){
  if(CHECK_PTR(pTree)){
    return 0;
  }

  pTree->pL = AvlCharRotationL(pTree->pL);
  return AvlCharRotationR(pTree);
}


void inorderChar(NodeAvlChar *pTree){
  if(!CHECK_PTR(pTree)){
    inorderChar(pTree->pL);
    //WIP
    //if Driver, if Step, if Town: printf..
    //printf("%d, nSteps: %i, distTot: %f\n", );
    inorderChar(pTree->pR);
  }
}