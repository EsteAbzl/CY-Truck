#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _avl_driver {
  char *name; // Avl_Str type so we sort by char*

  Avl_int *avl_path; // Avl_int to stock the path;
  float DistTot;     // Stock the total lenght of eachpath
  int path_nbr;      // Number of path stocked in path

  int equilibre;
  struct _avl_driver *pL;
  struct _avl_driver *pR;
} Avl_Driver;

Avl_Driver *createAvl_Driver(char *chaine) {
  Avl_Driver *pNew = malloc(sizeof(Avl_Driver));
  if (pNew == NULL) {
    exit(1);
  }
  pNew->name = chaine;
  pNew->equilibre = 0;
  pNew->pL = NULL;
  pNew->pR = NULL;
  return pNew;
}
int Avl_Driver_NULL(Avl_Driver *pTree) { return pTree == NULL; }

int Avl_Driver_LeftExist(Avl_Driver *pTree) {
  return !Avl_Driver_NULL(pTree) && !Avl_Driver_NULL(pTree->pL);
}

int Avl_Driver_RightExist(Avl_Driver *pTree) {
  return !Avl_Driver_NULL(pTree) && !Avl_Driver_NULL(pTree->pR);
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b)) // fct max

int high(Avl_Driver *pTree) { // hauteur
  int comptL = 0, comptR = 0;
  if (pTree == NULL) {
    return 0;
  }
  if (!Avl_Driver_LeftExist(pTree) && !Avl_Driver_LeftExist(pTree)) {
    return 1;
  } else {
    if (Avl_Driver_LeftExist(pTree)) {
      comptL = high(pTree->pL);
    }
    if (Avl_Driver_RightExist(pTree)) {
      comptR = high(pTree->pR);
    }
  }
  return MAX(comptL, comptR) + 1;
}

Avl_Driver *equilibrage_Driver(Avl_Driver *pTree);

Avl_Driver *AddAvl_Driver(Avl_Driver *pTree, char *chaine, int *h) {
  if (pTree == NULL) {
    // found the place to create new node
    *h = 1;
    return createAvl_Driver(chaine);
  } else if (strcmp(pTree->name, chaine) > 0) {
    // look into the left subtree
    pTree->pL = AddAvl_Driver(pTree->pL, chaine, h);
    *h = -*h;
  } else if (strcmp(pTree->name, chaine) < 0) {
    // look into the right subtree
    // h reste le mm
    pTree->pR = AddAvl_Driver(pTree->pR, chaine, h);
  } else {
    *h = 0;
    return pTree;
    // We have found the same value : do nothing
  }
  if (*h != 0) {
    pTree->equilibre = pTree->equilibre + *h;
    pTree = equilibrage_Driver(pTree);
    if (pTree->equilibre == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}

Avl_Driver *pre_AddAvl_Driver(Avl_Driver *pTree, char *chaine) {
  static int h = 0;
  return AddAvl_Driver(pTree, chaine, &h);
}

Avl_Driver *SuppMax_Driver(Avl_Driver *pTree, char **chaine);

Avl_Driver *DelAvl_Driver(Avl_Driver *pTree, char *chaine, int *h) {
  // element non présent dans l’arbre
  if (pTree == NULL) {
    *h = 1;
    return pTree;
  }
  // parcours récursif de l’arbre
  else if (strcmp(pTree->name, chaine) < 0) { // go a droite car elem plus grand
    pTree->pR = DelAvl_Driver(pTree->pR, chaine, h);
  } else if (strcmp(pTree->name, chaine) > 0) { // go a gauche car elem plus
                                                // ptit
    pTree->pL = DelAvl_Driver(pTree->pL, chaine, h);
    *h = -*h;
  }
  // élément trouvé : remplacement par fils unique
  else if (!Avl_Driver_LeftExist(pTree)){ // si il a pas de sous arbre gauche on remplace par
                         // sous arbre droit (fils unique)
    Avl_Driver *tmp;
    tmp = pTree;
    pTree = pTree->pR;
    free(tmp);
    *h = -1;
  }
  // élément trouvé : remplacement par prédécesseur
  else {
    pTree->pL = SuppMax_Driver(pTree->pL, &(pTree->name));
  }
  if (*h != 0) {
    pTree->equilibre = pTree->equilibre + *h;
    pTree = equilibrage_Driver(pTree);
    if (pTree->equilibre == 0) {
      *h = 0;
    } else {
      *h = -1;
    }
  }
  return pTree;
}

Avl_Driver *SuppMax_str(Avl_Driver *pTree, char **chaine) {
  Avl_Driver *tmp;
  if (Avl_Driver_RightExist(pTree)) {
    SuppMax_Driver(pTree->pR, chaine);
  } else {
    *chaine = pTree->name;
    tmp = pTree;
    pTree = pTree->pL;
    free(tmp);
  }
  return pTree;
}

Avl_Driver *pre_DelAvl_Driver(Avl_Driver *pTree, char *chaine) {
  static int h = 0;
  return DelAvl_Driver(pTree, chaine, &h);
}

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

Avl_Driver *Rota_G(Avl_Driver *pTree) {
  if (pTree == NULL || pTree->pR == NULL) {
    return 0;
  }
  Avl_Driver *Pivot = pTree->pR;

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

Avl_Driver *Rota_D(Avl_Driver *pTree) {
  if (pTree == NULL || pTree->pL == NULL) {
    return 0;
  }
  Avl_Driver *Pivot = pTree->pL;
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

Avl_Driver *RotaDouble_G(Avl_Driver *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pR = Rota_D(pTree->pR);
  return Rota_G(pTree);
}

Avl_Driver *RotaDouble_D(Avl_Driver *pTree) {
  if (pTree == NULL) {
    return 0;
  }
  pTree->pL = Rota_G(pTree->pL);
  return Rota_D(pTree);
}

Avl_Driver *equilibrage_str(Avl_Driver *pTree) {
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

void displayInfixe(Avl_Driver *p) {
  if (p != NULL) {
    displayInfixe(p->pL);
    printf("%s", p->name);
    displayInfixe(p->pR);
  }
}
