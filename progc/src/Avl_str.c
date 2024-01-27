#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Avl_str {
  char *name;
  // AvlInt trajet;
  int bFactor;
  struct _Avl_str *pL;
  struct _Avl_str *pR;
} Avl_str;

Avl_str *createAvl_str(char *str) {
  Avl_str *pNew = malloc(sizeof(Avl_str));
  if (pNew == NULL) {
    exit(1);
  }
  pNew->name = str;
  pNew->bFactor = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  return pNew;
}
int Avl_str_NULL(Avl_str *pTree) { return pTree == NULL; }

int Avl_str_LeftExist(Avl_str *pTree) {
  return !Avl_str_NULL(pTree) && !Avl_str_NULL(pTree->pL);
}

int Avl_str_RightExist(Avl_str *pTree) {
  return !Avl_str_NULL(pTree) && !Avl_str_NULL(pTree->pR);
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b)) // fct max

int AvlHeight(Avl_str *pTree) { // hauteur
  int comptL = 0, comptR = 0;
  if (pTree == NULL) {
    return 0;
  }
  if (!Avl_str_LeftExist(pTree) && !Avl_str_LeftExist(pTree)) {
    return 1;
  } else {
    if (Avl_str_LeftExist(pTree)) {
      comptL = AvlHeight(pTree->pL);
    }
    if (Avl_str_RightExist(pTree)) {
      comptR = AvlHeight(pTree->pR);
    }
  }
  return MAX(comptL, comptR) + 1;
}

Avl_str *equilibrage_str(Avl_str *pTree);

Avl_str *AddAvl_str(Avl_str *pTree, char *str, int *h) {
  if (pTree == NULL) {
    // found the place to create new node
    *h = 1;
    return createAvl_str(str);
  } else if (strcmp(pTree->name, str) > 0) {
    // look into the left subtree
    pTree->pL = AddAvl_str(pTree->pL, str, h);
    *h = -*h;
  } else if (strcmp(pTree->name, str) < 0) {
    // look into the right subtree
    // h reste le mm
    pTree->pR = AddAvl_str(pTree->pR, str, h);
  } else {
    *h = 0;
    return pTree;
    // We have found the same value : do nothing
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = equilibrage_str(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}

Avl_str *pre_AddAvl_str(Avl_str *pTree, char *str) {
  static int h = 0;
  return AddAvl_str(pTree, str, &h);
}

Avl_str *delAvlLargestStr(Avl_str *pTree, char **str);

Avl_str *DelAvl_str(Avl_str *pTree, char *str, int *h) {
  // element non présent dans l’arbre
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // parcours récursif de l’arbre
  else if (strcmp(pTree->name, str) < 0) { // go a droite car elem plus grand
    pTree->pR = DelAvl_str(pTree->pR, str, h);
  } else if (strcmp(pTree->name, str) > 0) { // go a gauche car elem plus
                                                // ptit
    pTree->pL = DelAvl_str(pTree->pL, str, h);
    *h = -*h;
  }
  // élément trouvé : remplacement par fils unique
  else if (!Avl_str_LeftExist(
               pTree)) { // si il a pas de sous arbre gauche on remplace par
                         // sous arbre droit (fils unique)
    Avl_str *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  // élément trouvé : remplacement par prédécesseur
  else {
    pTree->pL = delAvlLargestStr(pTree->pL, &(pTree->name));
  }
  if (*h != 0) {
    pTree->bFactor = pTree->bFactor + *h;
    pTree = equilibrage_str(pTree);
    if (pTree->bFactor == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}

Avl_str *delAvlLargestStr(Avl_str *pTree, char **str) {
  Avl_str *tmp;
  if (Avl_str_RightExist(pTree)) {
    delAvlLargestStr(pTree->pR, str);
  } else {
    *str = pTree->name;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

Avl_str *pre_DelAvl_str(Avl_str *pTree, char *str) {
  static int h = 0;
  return DelAvl_str(pTree, str, &h);
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

Avl_str *AvlRotationL(Avl_str *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  Avl_str *Pivot = pTree->pR;

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

Avl_str *AvlRotationR(Avl_str *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  Avl_str *Pivot = pTree->pL;
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

Avl_str *AvlRotationRL(Avl_str *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = AvlRotationR(pTree->pR);
  return AvlRotationL(pTree);
}

Avl_str *AvlRotationLR(Avl_str *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = AvlRotationL(pTree->pL);
  return AvlRotationR(pTree);
}

Avl_str *equilibrage_str(Avl_str *pTree) {
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

void displayInfixe(Avl_str *p) {
  if (p != NULL) {
    displayInfixe(p->pL);
    printf("%s", p->name);
    displayInfixe(p->pR);
  }
}
