#include <stdio.h>
#include <stdlib.h>

typedef struct _tree{
    int value;
    struct _tree* pLeft;
    struct _tree* pRight;
}Tree;

Tree* createTree(int v){
    Tree* pNew = malloc(sizeof(Tree));
    if(pNew==NULL){
        exit(1);
    }
    pNew->value = v;
    pNew->pLeft = NULL;
    pNew->pRight = NULL;
    return pNew;
}

int isEmpty(Tree* p){
    return p == NULL;
}

int isLeaf(Tree* p){
    return !isEmpty(p) && isEmpty(p->pLeft) && isEmpty(p->pRight);
}

int getValue(Tree* p){
    if(p==NULL){
        printf("[Débug] [getValue] Arbre donné vide.\n");
        exit(2);
    }
    return p->value;
}

int hasLeftChild(Tree* p){
    return !isEmpty(p) && !isEmpty(p->pLeft);
}

int hasRightChild(Tree* p){
    return !isEmpty(p) && !isEmpty(p->pRight);
}

int addLeftChild(Tree* p, int v){
    if(hasLeftChild(p)){
        return 0;
    }
    p->pLeft = createTree(v);
    return p->pLeft != NULL; //vérification de si l'allocation a fonctionné
}

int addRightChild(Tree* p, int v){
    if(hasRightChild(p)){
        return 0;
    }
    p->pRight = createTree(v);
    return p->pRight != NULL; //vérification de si l'allocation a fonctionné
}

void traiter(Tree* p){
    if(isEmpty(p)){
        exit(3);
    }
    printf("[%02d]",p->value);
}

// Exercice 3 :

int isFiliforme(Tree* p){
    if(!(p==NULL)){
        if(!(hasLeftChild(p) && hasRightChild(p))){
            return (1 && (isFiliforme(p->pLeft) && isFiliforme(p->pRight)));
        }
        else{
            return 0;
        }
    }
    return 1;
}

int peigneGauche(Tree* p){
    if(!(p==NULL)){
        if(!(hasRightChild(p)) && hasLeftChild(p)){
            return (1 && peigneGauche(p->pLeft));
        }
        else{
            return 0;
        }
    }
    return 1;
}

Tree* constrPeigneGauche(int h){
    Tree* pNew = createTree(rand()%11);
    Tree * pTmp = pNew;
    for(int i=0;i<h;i++){
        pTmp->pLeft = createTree(rand()%11);
        pTmp = pTmp->pLeft;
    }
    return pNew;
}

/*Exercice 3 (Arbre binaire filiforme)
Un arbre binaire est dit filiforme si chaque nœud a au plus un seul fils (qu’il soit gauche ou droit).
— A quoi va ressembler un tel arbre ?
— Écrire une fonction permettant de determiner si un arbre est filiforme (plusieurs méthodes sont possibles !).
— Un arbre est dit peigne gauche si les nœuds n’ont qu’un fils gauche et pas de fils droit.
— Écrire une fonction permettant de determiner si un arbre est peigne gauche.
— Écrire une fonction parbre constrPeigneGauche(int h) qui va créer un arbre peigne gauche de hauteur h en le
remplissant avec des valeurs aléatoires entre 0 et 10. L’afficher.*/

int main(){

    //Locals
    Tree* pTree = NULL;

    //Root (layer 0)
    pTree = createTree(1);
    //Layer 1
    addLeftChild(pTree, 2);
    //Layer 2
    addRightChild(pTree->pLeft, 6);
    //Leaf (layer 3)
    addLeftChild(pTree->pLeft->pRight, 4);

    int i = isFiliforme(pTree);
    int j = peigneGauche(pTree);
    printf("isFiliforme : %d\npeigneGauche : %d\n",i,j);
    Tree* p = constrPeigneGauche(3);
    int k = peigneGauche(p);
    printf("peigneGauche p : %d\n",k);

    return 0;
}