#include <stdio.h>
#include <stdlib.h>


typedef struct _Avl {
    int           value;
    int bFactor;
    struct _Avl* pL;
    struct _Avl* pR;
} Avl;

Avl * createAvl(int v){
    Avl* pNew = malloc(sizeof(Avl));
    if(pNew == NULL){
        exit(1);
    }
    pNew->value = v;
    pNew->bFactor = 0;
    pNew->pL    = NULL;
    pNew->pR    = NULL;
    return pNew;
} 
int AvlNULL(Avl* pTree){
    return pTree == NULL;
}

int AvlLeftExist(Avl * pTree){
    return !AvlNULL(pTree) && !AvlNULL(pTree->pL);
}

int AvlRightExist(Avl * pTree){
    return !AvlNULL(pTree) && !AvlNULL(pTree->pR);
}

#define MAX(a,b) (((a)>(b))?(a):(b)) //fct max

int AvlHeight(Avl * pTree){ //hauteur
    int comptL=0,comptR=0;
    if(pTree==NULL){
        return 0;
    }
    if(!AvlLeftExist(pTree) && !AvlLeftExist(pTree)){
        return 1;
    }
    else{
        if(AvlLeftExist(pTree)){
            comptL = AvlHeight(pTree->pL);
        }
        if(AvlRightExist(pTree)){
            comptR = AvlHeight(pTree->pR); 
        }
    }
    return MAX(comptL,comptR)+1;
}

Avl * equilibrage(Avl * pTree);

Avl* addAvl(Avl* p, int v,int *h){
    if(p == NULL){
        // found the place to create new node
        *h = 1;
        return createAvl(v);
    }
    else if(v < p->value){
        // look into the left subtree
        p->pL = addAvl(p->pL, v,h);
        *h = -*h;
    }
    else if(v > p->value){
        // look into the right subtree
        //h reste le mm
        p->pR = addAvl(p->pR, v,h);
    }
    else{
        *h = 0;
        return p;
        // We have found the same value : do nothing
    }   
    if(*h != 0){
        p->bFactor = p->bFactor+*h;
        p = equilibrage(p);
        if(p->bFactor==0){
            *h = 0;
        }
        else{
            *h = -1;
        }
    }
    return p;
}

Avl* SuppMax(Avl* pTree, int* elem);

Avl* delABR(Avl * pTree, int elem,int *h){
    // element non présent dans l’arbre
    if(pTree == NULL){
        *h = 1;
        return pTree;
    }
    // parcours récursif de l’arbre
    else if(pTree->value < elem){           //go a droite car elem plus grand
        pTree->pR = delABR(pTree->pR,elem,h);
    }
    else if(pTree->value > elem){           //go a gauche car elem plus ptit
        pTree->pL = delABR(pTree->pL,elem,h);
        *h =-*h;
    }
    // élément trouvé : remplacement par fils unique
    else if (!AvlLeftExist(pTree)){ //si il a pas de sous arbre gauche on remplace par sous arbre droit (fils unique)
        Avl* tmp;
        tmp = pTree;
        pTree = pTree->pR;
        free(tmp);
        *h = -1;
    }
    // élément trouvé : remplacement par prédécesseur
    else{
        pTree->pL = SuppMax(pTree->pL, &(pTree->value));
    }
    if(*h != 0){
        pTree->bFactor = pTree->bFactor+*h;
        pTree = equilibrage(pTree);
        if(pTree->bFactor==0){
            *h = 0;
        }
        else{
            *h = -1;
        }
    }
    return pTree;
}

Avl* SuppMax(Avl* pTree, int* elem){
    Avl * tmp;
    if(AvlRightExist(pTree)){
        SuppMax(pTree->pR,elem);
    }
    else{
        *elem = pTree->value;
        tmp = pTree;
        pTree = pTree->pL;
        free(tmp);
    }
    return pTree;
}

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

Avl * AvlRotationL(Avl * pTree){
    if(pTree==NULL||pTree->pR == NULL){
        return 0;
    }
    Avl * Pivot = pTree->pR;
    
    pTree->pR = Pivot->pL;
    Pivot->pL = pTree;
    
    //verif equilibrage
    int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
    pTree->bFactor -= MAX(eq_Pivot,0) - 1; 
    Pivot->bFactor = MIN(eq_Ptree + eq_Pivot - 2,MIN(eq_Ptree - 2,eq_Pivot-1));
    
    pTree = Pivot;
    return pTree;    
}

Avl * AvlRotationR(Avl * pTree){
    if(pTree==NULL||pTree->pL == NULL){
        return 0;
    }
    Avl * Pivot = pTree->pL;
    pTree ->pL = Pivot->pR;
    Pivot->pR = pTree;
    
    //verif equilibrage
    int eq_Ptree = pTree->bFactor, eq_Pivot = Pivot->bFactor;
    pTree->bFactor -= MIN(eq_Pivot,0) + 1; 
    Pivot->bFactor = MAX(eq_Ptree + eq_Pivot + 2,MAX(eq_Ptree + 2,eq_Pivot+1));
    
    pTree = Pivot;
    return pTree;    
}

Avl * AvlRotationRL(Avl * pTree){
    if(pTree==NULL){
        return 0;
    }
    pTree->pR = AvlRotationR(pTree->pR);
    return AvlRotationL(pTree);
}

Avl * AvlRotationLR(Avl * pTree){
    if(pTree==NULL){
        return 0;
    }
    pTree->pL = AvlRotationL(pTree->pL);
    return AvlRotationR(pTree);
}

Avl * equilibrage(Avl * pTree){
    if(pTree==NULL){
        return pTree;
    }
    else if(pTree->bFactor >=2){
        if(pTree->pR==NULL){
            exit(1);
        }
        if(pTree->pR->bFactor >= 0){
            return AvlRotationL(pTree);
        }
        else{
            return AvlRotationRL(pTree);
        }
    }
    else if(pTree->bFactor <=-2){
        if(pTree->pL==NULL){
            exit(1);
        }
        if(pTree->pL->bFactor <= 0){
            return AvlRotationR(pTree);
        }
        else{
            return AvlRotationLR(pTree);
        }
    }
    return pTree;
}

void displayInfixe(Avl* p){
    if(p !=NULL){
        displayInfixe(p->pL);
        printf("[%3d]\n",p->value);
        displayInfixe(p->pR);
    }
}


int main(){
    Avl* p = NULL;
    int h=0;
    p = createAvl(10);
    p = addAvl(p, 5,&h);
    h=0;
    p = addAvl(p, 20,&h);
    h=0;
    p = addAvl(p, 15,&h);
    h=0;
    p = addAvl(p, 26,&h);
    h=0;
    p = addAvl(p, 13,&h);
    h=0;
    p = addAvl(p, 17,&h);
    h=0;


    return 0;
}