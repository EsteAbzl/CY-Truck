#include <stdio.h>
#include <stdlib.h>

typedef struct _avl_int {
  int value; // Sort by value

  int equilibre;
  struct _avl_int *pL;
  struct _avl_int *pR;
} Avl_int;

Avl_int *createAvl(int v) {
  Avl_int *pNew = malloc(sizeof(Avl_int));
  if (pNew == NULL) {
    exit(1);
  }
  pNew->value = v;
  pNew->equilibre = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  return pNew;
}
int AvlNULL(Avl_int *pTree) { return pTree == NULL; }

int AvlLeftExist(Avl_int *pTree) {
  return !AvlNULL(pTree) && !AvlNULL(pTree->pL);
}

int AvlRightExist(Avl_int *pTree) {
  return !AvlNULL(pTree) && !AvlNULL(pTree->pR);
}

Avl_int *equilibrage(Avl_int *pTree);

Avl_int *AddAvl_int(Avl_int *p, int v, int *h) {
  if (p == NULL) {
    // found the place to create new node
    *h = 1;
    return createAvl(v);
  } else if (v < p->value) {
    // look into the left subtree
    p->pL = AddAvl_int(p->pL, v, h);
    *h = -*h;
  } else if (v > p->value) {
    // look into the right subtree
    // h reste le mm
    p->pR = AddAvl_int(p->pR, v, h);
  } else {
    *h = 0;
    return p;
    // We have found the same value : do nothing
  }
  if (*h != 0) {
    p->equilibre = p->equilibre + *h;
    p = equilibrage(p);
    if (p->equilibre == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return p;
}

Avl_int *pre_AddAvl_int(Avl_int *pTree, int elem) {
  static int h = 0;
  return AddAvl_int(pTree, elem, &h);
}

Avl_int *SuppMax_int(Avl_int *pTree, int *elem);

Avl_int *DelAvl_int(Avl_int *pTree, int elem, int *h) {
  // element non présent dans l’arbre
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // parcours récursif de l’arbre
  else if (pTree->value < elem) { // go a droite car elem plus grand
    pTree->pR = DelAvl_int(pTree->pR, elem, h);
  } else if (pTree->value > elem) { // go a gauche car elem plus ptit
    pTree->pL = DelAvl_int(pTree->pL, elem, h);
    *h = -*h;
  }
  // élément trouvé : remplacement par fils unique
  else if (!AvlLeftExist(pTree)) { // si il a pas de sous arbre gauche on remplace par
                         // sous arbre droit (fils unique)
    Avl_int *tmp;
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
    pTree->equilibre = pTree->equilibre + *h;
    pTree = equilibrage(pTree);
    if (pTree->equilibre == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}

Avl_int *SuppMax_int(Avl_int *pTree, int *elem) {
  Avl_int *tmp;
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

Avl_int *pre_DelAvl_int(Avl_int *pTree, int elem) {
  static int h = 0;
  return DelAvl_int(pTree, elem, &h);
}

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

Avl_int *Rota_G(Avl_int *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  Avl_int *Pivot = pTree->pR;

  pTree->pR = Pivot->pL;
  Pivot->pL = pTree;

  // verif equilibrage
  int eq_Ptree = pTree->equilibre, eq_Pivot = Pivot->equilibre;
  pTree->equilibre -= max(eq_Pivot, 0) - 1;
  Pivot->equilibre =
      min(eq_Ptree + eq_Pivot - 2, min(eq_Ptree - 2, eq_Pivot - 1));

  pTree = Pivot;
  return pTree;
}

Avl_int *Rota_D(Avl_int *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  Avl_int *Pivot = pTree->pL;
  pTree->pL = Pivot->pR;
  Pivot->pR = pTree;

  // verif equilibrage
  int eq_Ptree = pTree->equilibre, eq_Pivot = Pivot->equilibre;
  pTree->equilibre -= min(eq_Pivot, 0) + 1;
  Pivot->equilibre =
      max(eq_Ptree + eq_Pivot + 2, max(eq_Ptree + 2, eq_Pivot + 1));

  pTree = Pivot;
  return pTree;
}

Avl_int *RotaDouble_G(Avl_int *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = Rota_D(pTree->pR);
  return Rota_G(pTree);
}

Avl_int *RotaDouble_D(Avl_int *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = Rota_G(pTree->pL);
  return Rota_D(pTree);
}

Avl_int *equilibrage(Avl_int *pTree) {
  if (pTree == NULL) {
    return pTree;
  } else if (pTree->equilibre >= 2) {
    if (pTree->pR == NULL) {
      exit(1);
    }
    if (pTree->pR->equilibre >= 0) {
      return Rota_G(pTree);
    } else {
      return RotaDouble_G(pTree);
    }
  } else if (pTree->equilibre <= -2) {
    if (pTree->pL == NULL) {
      exit(1);
    }
    if (pTree->pL->equilibre <= 0) {
      return Rota_D(pTree);
    } else {
      return RotaDouble_D(pTree);
    }
  }
  return pTree;
}
