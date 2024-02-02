#include "AVL_BasicInt.h"

AvlBasicInt* init_AvlBasicInt(){
  AvlBasicInt *pNew = malloc(sizeof(AvlBasicInt));
  if (CHECK_PTR(pNew)) exit(1);

  pNew->h = 0;
  pNew->pRoot = NULL;

  return pNew;
}

NodeAvlBasicInt* create_NodeAvlBasicInt(int id){
  NodeAvlBasicInt *pNew = malloc(sizeof(NodeAvlBasicInt));
  if(CHECK_PTR(pNew)) exit(1);

  pNew->value = id;

  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  
  return pNew;
}

void free_SingularNodeAvlBasicInt(NodeAvlBasicInt* pTree){
  if(pTree){
    free(pTree);
  }
}

void free_NodeAvlBasicInt(NodeAvlBasicInt* pTree){
  if(pTree){
    free_NodeAvlBasicInt(pTree->pL);
    free_NodeAvlBasicInt(pTree->pR);

    free(pTree);
  }
}

void free_AvlBasicInt(AvlBasicInt* pAvl){
  if(pAvl){
    free_NodeAvlBasicInt(pAvl->pRoot);

    free(pAvl);
  }
}



void add_AvlBasicInt(AvlBasicInt *pAvl, int id){
  pAvl->pRoot = add_NodeAvlBasicInt(pAvl->pRoot, id, &pAvl->h);
}

NodeAvlBasicInt* add_NodeAvlBasicInt(NodeAvlBasicInt *pTree, int id, int *h) {
  if(pTree == NULL){                // If in a leaf, add the node there
    *h = 1;
    return create_NodeAvlBasicInt(id);
  } 
  else if(id > pTree->value){
    pTree->pR = add_NodeAvlBasicInt(pTree->pR, id, h);
  }
  else if(id < pTree->value){
    // If the new node's value is lesser, check the left branch
    pTree->pL = add_NodeAvlBasicInt(pTree->pL, id, h);
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



void del_AvlBasicInt(AvlBasicInt *pAvl, int id){
  pAvl->pRoot = del_NodeAvlBasicInt(pAvl->pRoot, &id, &pAvl->h);
}

NodeAvlBasicInt* del_NodeAvlBasicInt(NodeAvlBasicInt *pTree, int *id, int *h){
  if(pTree == NULL){   // Element not in tree
    *h = 1;
    return pTree;
  }
  else if(*id > pTree->value){   // Recursively search through the BST
    pTree->pR = del_NodeAvlBasicInt(pTree->pR, id, h);
  } 
  else if(*id < pTree->value){
    pTree->pL = del_NodeAvlBasicInt(pTree->pL, id, h);
    *h = -*h;
  }

  // Element found, replace as needed
  if(!(pTree->pL)){
    NodeAvlBasicInt *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free_SingularNodeAvlBasicInt(tmp);
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

NodeAvlBasicInt* del_AvlLargestBasicInt(NodeAvlBasicInt *pTree, int *id) {
  NodeAvlBasicInt *tmp;
  if(checkRightAvlBasicInt(pTree)){
    del_AvlLargestBasicInt(pTree->pR, id);
  } 
  else{
    *id = pTree->value;
    tmp = pTree;
    pTree = pTree->pL;
    free_SingularNodeAvlBasicInt(tmp);
  }

  return pTree;
}


NodeAvlBasicInt* isInAvlBasicInt(NodeAvlBasicInt *pTree, int id){
  NodeAvlBasicInt* ret = NULL;
  if(pTree == NULL){            // Return NULL if not found
    ret = NULL;
  } 
  else if(id < pTree->value) {  // Search value lower than current value, go left
    ret = isInAvlBasicInt(pTree->pL, id);
  } 
  else if (id > pTree->value) { // Search value higher than current value, go right
    ret = isInAvlBasicInt(pTree->pR, id);
  } 
  else {                        // Return the current node if found
    ret = pTree;
  }
  return ret;
}


int checkLeftAvlBasicInt(NodeAvlBasicInt *ptr){
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pL);
}

int checkRightAvlBasicInt(NodeAvlBasicInt *ptr){
  return !CHECK_PTR(ptr) && !CHECK_PTR(ptr->pR);
}


NodeAvlBasicInt *balanceAvlBasicInt(NodeAvlBasicInt *pTree){
  if(pTree == NULL){
    return pTree;
  }
  else if(pTree->bFactor >= 2){
    if(pTree->pR == NULL){
      exit(1);
    }

    if(pTree->pR->bFactor >= 0){
      return avlBasicIntRotationL(pTree);
    }
    else{
      return avlBasicIntRotationRL(pTree);
    }
  } 
  else if(pTree->bFactor <= -2){
    if(pTree->pL == NULL){
      exit(1);
    }

    if(pTree->pL->bFactor <= 0){
      return avlBasicIntRotationR(pTree);
    }
    else{
      return avlBasicIntRotationLR(pTree);
    }
  }

  return pTree;
}


NodeAvlBasicInt *avlBasicIntRotationL(NodeAvlBasicInt *pTree){
  if(!checkRightAvlBasicInt(pTree)){
    return 0;
  }

  NodeAvlBasicInt *Pivot = pTree->pR;
  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));
  pTree = Pivot;

  return pTree;
}

NodeAvlBasicInt *avlBasicIntRotationR(NodeAvlBasicInt *pTree){
  if(!checkLeftAvlBasicInt(pTree)){
    return 0;
  }

  NodeAvlBasicInt *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // check balancing
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor = eq_Ptree - MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));
  pTree = Pivot;

  return pTree;
}

NodeAvlBasicInt *avlBasicIntRotationRL(NodeAvlBasicInt *pTree){
  if(CHECK_PTR(pTree)){
    return 0;
  }

  pTree->pR = avlBasicIntRotationR(pTree->pR);
  return avlBasicIntRotationL(pTree);
}

NodeAvlBasicInt *avlBasicIntRotationLR(NodeAvlBasicInt *pTree){
  if(CHECK_PTR(pTree)){
    return 0;
  }

  pTree->pL = avlBasicIntRotationL(pTree->pL);
  return avlBasicIntRotationR(pTree);
}


void inorderBasicInt(NodeAvlBasicInt *pTree){
  if(!CHECK_PTR(pTree)){
    inorderBasicInt(pTree->pL);
    printf("value:%d\n", pTree->value);
    inorderBasicInt(pTree->pR);
  }
}