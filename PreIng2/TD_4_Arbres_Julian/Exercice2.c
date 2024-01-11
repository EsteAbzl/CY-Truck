#include <stdio.h>
#include <stdlib.h>

typedef struct _tree{
    int value;
    struct _tree* pLeft;
    struct _tree* pRight;
}Tree;

//typedef Tree* PTree;

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

void prefix(Tree* p){
    if(!isEmpty(p)){
        traiter(p);
        prefix(p->pLeft);
        prefix(p->pRight);
    }
}

void postfix(Tree* p){
    if(!isEmpty(p)){
        postfix(p->pLeft);
        postfix(p->pRight);
        traiter(p);
    }
}

typedef struct _treelist{
    Tree* value;
    struct _treelist* pNext;
}TreeList;

typedef struct _treefifo{
    TreeList* pFirst;
    TreeList* pLast;
    int size;
}TreeFifo;

TreeFifo* createTreeFifo(){
    TreeFifo* pNew = malloc(sizeof(TreeFifo));
    if(pNew==NULL){
        exit(4);
    }
    pNew->pFirst = NULL;
    pNew->pLast = NULL;
    pNew->size = 0;
    return pNew;
}

TreeList* createTreeList(Tree* p){
    TreeList* pNew = malloc(sizeof(TreeList));
    if(pNew == NULL){
        exit(5);
    }
    pNew->value = p;
    pNew->pNext = NULL;
    return pNew;
}

TreeList* addListEnd(TreeList* pList, Tree* pTree){
    TreeList* pNew = createTreeList(pTree);
    TreeList* pTmp = pList; 
    if(pList==NULL){
        return pNew;
    }
    while(pTmp->pNext!=NULL){
        pTmp = pTmp->pNext;
    }
    pTmp->pNext = pNew;
    return pList;
}

int isFifoEmpty(TreeFifo* f){
    return f->pFirst==NULL && f->pLast==NULL;
}

void pushFifo(TreeFifo* f, Tree* p){ //enfiler
    // Check params
    if(f == NULL || p == NULL){
        exit(6);
    }
    
    f->pLast = addListEnd(f->pLast,p);
    if(f->pFirst==NULL){
        f->pFirst = f->pLast;
    }
    else{
        f->pLast = f->pLast->pNext;
    }
}

Tree* popFifo(TreeFifo* f){ //defiler
    TreeList* pTmp = NULL;
    Tree* treeTmp = NULL;
    
    if(f == NULL){
        exit(7);
    }
    if(f->pFirst == NULL){
        return NULL;
    }
    pTmp = f->pFirst;
    f->pFirst = pTmp->pNext;
    treeTmp = pTmp->value;
    if(f->pFirst==NULL){
        f->pLast=NULL;
    }
    free(pTmp);
    return treeTmp;
}

void parcoursLargeur(Tree* p){ //a = p et f reste f
    Tree* pTmp;
    TreeFifo* f;

    if(!isEmpty(p)){
        f = createTreeFifo();
        pushFifo(f,p);
        while(!isFifoEmpty(f)){
            pTmp = popFifo(f);
            traiter(pTmp);
            if(hasLeftChild(pTmp)){
                pushFifo(f,pTmp->pLeft);//enfiler(f,fg(pTmp));
            }
            if(hasRightChild(pTmp)){
                pushFifo(f,pTmp->pRight);//enfiler(f,fd(mTmp));
            }
        }
    }
}

//Partie 3 :

Tree* modifierRacine(Tree* a, int e){
    if(a==NULL){
        exit(8);
    }
    a->value = e;
    return a;
}

void supprimerFilsGauche(Tree* p);
void supprimerFilsDroit(Tree* p);

void supprimerFilsGauche(Tree* p){
    if(p==NULL){
        exit(9);
    }
    if(p->pLeft != NULL){
        supprimerFilsGauche(p->pLeft);
        supprimerFilsDroit(p->pLeft);
        free(p->pLeft);
        p->pLeft = NULL;
    }
}

void supprimerFilsDroit(Tree* p){
    if(p==NULL){
        exit(9);
    }
    if(p->pRight != NULL){
        supprimerFilsGauche(p->pRight);
        supprimerFilsDroit(p->pRight);
        free(p->pRight);
        p->pRight = NULL;
    }
}

int nmbFeuille(Tree* p){
    if(!(p==NULL)){
        if(p->pLeft==NULL && p->pRight==NULL){
            return 1;
        }
        else{
            return nmbFeuille(p->pLeft) + nmbFeuille(p->pRight);
        }
    }
}

int tailleArbreREC(Tree* p){
    if(!(p==NULL)){
        return 1 + tailleArbreREC(p->pLeft) + tailleArbreREC(p->pRight);
    }
}
int tailleArbre(Tree* p){
    return tailleArbreREC(p) - 1;
}

int max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
int hauteur(Tree* p){
    if(!(p==NULL)){
        return 1 + max(hauteur(p->pLeft),hauteur(p->pRight));
    }
}

int main(){

    //Locals
    Tree* pTree = NULL;

    //Root (layer 0)
    pTree = createTree(1);
    //Layer 1
    addLeftChild(pTree, 2);
    addRightChild(pTree, 8);
    //Layer 2
    addLeftChild(pTree->pLeft, 3);
    addRightChild(pTree->pLeft, 6);
    addLeftChild(pTree->pRight, 9);
    addRightChild(pTree->pRight, 10);
    //Leaf (layer 3)
    addLeftChild(pTree->pLeft->pLeft, 4);
    addRightChild(pTree->pLeft->pLeft, 5);
    addRightChild(pTree->pLeft->pRight, 7);

    printf("Parcours Prefixe : ");
    prefix(pTree);
    printf("\n");

    printf("Parcours Postfixe : ");
    postfix(pTree);
    printf("\n");

    printf("Parcours Largeur : ");
    parcoursLargeur(pTree);
    printf("\n");

    int i = nmbFeuille(pTree);
    int j = tailleArbre(pTree);
    int k = hauteur(pTree);
    printf("Nombre de feuilles : %d\nTaille de l'arbre : %d\nHauteur de l'arbre : %d\n",i,j,k);


    return 0;
}