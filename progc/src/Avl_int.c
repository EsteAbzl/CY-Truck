#include <stdio.h>
#include <stdlib.h>

typedef struct _AvlInt {
  int value; // Sort by value

  int bFactor;
  struct _AvlInt *pL;
  struct _AvlInt *pR;
} AvlInt;

AvlInt *createAvl(int v) {
  AvlInt *pNew = malloc(sizeof(AvlInt));
  if (pNew == NULL) {
    exit(1);
  }
  pNew->value = v;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  return pNew;
}
int AvlNULL(AvlInt *pTree) { return pTree == NULL; }

int AvlLeftExist(AvlInt *pTree) {
  return !AvlNULL(pTree) && !AvlNULL(pTree->pL);
}

int AvlRightExist(AvlInt *pTree) {
  return !AvlNULL(pTree) && !AvlNULL(pTree->pR);
}

AvlInt *equilibrage(AvlInt *pTree);

AvlInt *AddAvlInt(AvlInt *p, int v, int *h) {
  if (p == NULL) {
    // found the place to create new node
    *h = 1;
    return createAvl(v);
  } else if (v < p->value) {
    // look into the left subtree
    p->pL = AddAvlInt(p->pL, v, h);
    *h = -*h;
  } else if (v > p->value) {
    // look into the right subtree
    // h reste le mm
    p->pR = AddAvlInt(p->pR, v, h);
  } else {
    *h = 0;
    return p;
    // We have found the same value : do nothing
  }
  if (*h != 0) {
    p->bFactor = p->bFactor + *h;
    p = equilibrage(p);
    if (p->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return p;
}

AvlInt *pre_AddAvlInt(AvlInt *pTree, int elem) {
  static int h = 0;
  return AddAvlInt(pTree, elem, &h);
}

AvlInt *SuppMax_int(AvlInt *pTree, int *elem);

AvlInt *DelAvlInt(AvlInt *pTree, int elem, int *h) {
  // element non présent dans l’arbre
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // parcours récursif de l’arbre
  else if (pTree->value < elem) { // go a droite car elem plus grand
    pTree->pR = DelAvlInt(pTree->pR, elem, h);
  } else if (pTree->value > elem) { // go a gauche car elem plus ptit
    pTree->pL = DelAvlInt(pTree->pL, elem, h);
    *h = -*h;
  }
  // élément trouvé : remplacement par fils unique
  else if (!AvlLeftExist(pTree)) { // si il a pas de sous arbre gauche on remplace par
                         // sous arbre droit (fils unique)
    AvlInt *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  // élément trouvé : remplacement par prédécesseur
  else {
    pTree->pL = SuppMax_int(pTree->pL, &(pTree->value));
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

AvlInt *SuppMax_int(AvlInt *pTree, int *elem) {
  AvlInt *tmp;
  if (AvlRightExist(pTree)) {
    SuppMax_int(pTree->pR, elem);
  } else {
    *elem = pTree->value;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

AvlInt *pre_DelAvlInt(AvlInt *pTree, int elem) {
  static int h = 0;
  return DelAvlInt(pTree, elem, &h);
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

AvlInt *avlRotationL(AvlInt *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  AvlInt *Pivot = pTree->pR;

  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // verif equilibrage
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor -= MAX(eq_Pivot, 0) - 1;
  Pivot->bFactor =
      MIN(eq_Ptree + eq_Pivot - 2, MIN(eq_Ptree - 2, eq_Pivot - 1));

  pTree = Pivot;
  return pTree;
}

AvlInt *avlRotationR(AvlInt *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  AvlInt *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // verif equilibrage
  int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
  pTree->bFactor -= MIN(eq_Pivot, 0) + 1;
  Pivot->bFactor =
      MAX(eq_Ptree + eq_Pivot + 2, MAX(eq_Ptree + 2, eq_Pivot + 1));

  pTree = Pivot;
  return pTree;
}

AvlInt *avlRotationRL(AvlInt *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = avlRotationR(pTree->pR);
  return avlRotationL(pTree);
}

AvlInt *avlRotationLR(AvlInt *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = avlRotationL(pTree->pL);
  return avlRotationR(pTree);
}

AvlInt *equilibrage(AvlInt *pTree) {
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
