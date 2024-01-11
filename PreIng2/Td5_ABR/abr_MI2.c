#include <stdio.h>
#include <stdlib.h>


typedef struct _tree {
    int           value;
    struct _tree* pL;
    struct _tree* pR;
} Tree;


Tree* createTree(int v){
    Tree* pNew = malloc(sizeof(Tree));
    if(pNew == NULL){
        exit(1);
    }
    pNew->value = v;
    pNew->pL    = NULL;
    pNew->pR    = NULL;
    return pNew;
} 

void displayInfixe(Tree* p){
    if(p !=NULL){
        displayInfixe(p->pL);
        printf("[%3d]\n",p->value);
        displayInfixe(p->pR);
    }
}
void displayPrefixe(Tree* p){
    if(p !=NULL){
        printf("[%3d]\n",p->value);
        displayPrefixe(p->pL);
        displayPrefixe(p->pR);
    }
}

int rhPrefixe(Tree* p,int val, int* nbr_parcouru){
    if(p !=NULL){
        (*nbr_parcouru)++;
        if(p->value == val){
            return 1;
        }
        else if(rhPrefixe(p->pL,val,nbr_parcouru)){
            return 1;
        }
        else if(rhPrefixe(p->pR,val,nbr_parcouru)){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

int TreeNULL(Tree * pTree){
    return pTree == NULL;
}

int TreeLeftExist(Tree * pTree){
    return !TreeNULL(pTree) && !TreeNULL(pTree->pL);
}

int TreeRightExist(Tree * pTree){
    return !TreeNULL(pTree) && !TreeNULL(pTree->pR);
}

Tree* addABR(Tree* p, int v){
    if(p == NULL){
        // found the place to create new node
        p = createTree(v);
        if(p == NULL){
            exit(2);
        }        
    }
    else if(v < p->value){
        // look into the left subtree
        p->pL = addABR(p->pL, v);
    }
    else if(v > p->value){
        // look into the right subtree
        p->pR = addABR(p->pR, v);
    }
    else{
        // We have found the same value : do nothing
    }   
    // return the address (may be new)
    return p;
}

//pour l'itératif ce fait par boucle while en gardant en mémoire le noeud actuel


int isInABR(Tree* p, int v, int* nbr_parcouru){ //fonction de recherche
    if(nbr_parcouru ==NULL){
        exit(1);
    }
    if(p == NULL){
        return 0;        
    }
    else if(v < p->value){
        // look into the left subtree
        (*nbr_parcouru)++;
        return isInABR(p->pL, v,nbr_parcouru);
    }
    else if(v > p->value){
        // look into the right subtree
        (*nbr_parcouru)++;
        return isInABR(p->pR, v,nbr_parcouru);
    }
    else{
        (*nbr_parcouru)++;
        return 1;
    }   
}

// pPrevious pointeur sur la valeur du noeud précédent (dans le parcours infixe)
//REVOIR
int isABR(Tree* pTree, int** ppPrevious){
    if(ppPrevious == NULL){
        exit(99);
    }
    
    if(pTree != NULL){        
        if( !isABR(pTree->pL, ppPrevious) ){
            return 0;
        }
        // Process
        if(*ppPrevious != NULL){
            // compare previous value with current value
            if(**ppPrevious >= pTree->value){
                return 0;
            }
        }
        *ppPrevious = &(pTree->value);
        
        if( !isABR(pTree->pR, ppPrevious) ){
            return 0;
        }
    }
    return 1;
}


//FONCTION DE SUPPRESION
Tree* SuppMax(Tree* pTree, int* elem){
    Tree * tmp;
    if(TreeRightExist(pTree)){
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


Tree* SuppMin(Tree* pTree, int* elem){
    Tree * tmp;
    if(TreeLeftExist(pTree)){
        SuppMin(pTree->pL,elem);
    }
    else{
        *elem = pTree->value;
        tmp = pTree;
        pTree = pTree->pR;
        free(tmp);
    }
    return pTree;
}


Tree* delABR(Tree * pTree, int elem){
    // element non présent dans l’arbre
    if(pTree == NULL){
        return pTree;
    }
    // parcours récursif de l’arbre
    else if(pTree->value < elem){           //go a droite car elem plus grand
        pTree->pR = delABR(pTree->pR,elem);
    }
    else if(pTree->value > elem){           //go a gauche car elem plus ptit
        pTree->pL = delABR(pTree->pL,elem);
    }
    // élément trouvé : remplacement par fils unique
    else if (!TreeLeftExist(pTree)){ //si il a pas de sous arbre gauche on remplace par sous arbre droit (fils unique)
        Tree* tmp;
        tmp = pTree;
        pTree = pTree->pR;
        free(tmp);
    }
    // élément trouvé : remplacement par prédécesseur
    else{
        pTree->pL = SuppMax(pTree->pL, &(pTree->value));
    }

    //version SuppMin:
    /*
    else if(!TreeRightExist(pTree)){ //si il a pas de sous arbre droit on remplace par sous arbre gauche (fils unique)
        Tree* tmp;
        tmp = pTree;
        pTree = pTree->pL;
        free(tmp);
    }
    // élément trouvé : remplacement par prédécesseur
    else{
        pTree->pR = SuppMax(pTree->pR, &(pTree->value));
    }
    */
    return pTree;
}

//Fin fct suppression


int main(){

    Tree* p = NULL;

    p = addABR(p,10);
    p = addABR(p,3);
    p = addABR(p,5);
    p = addABR(p,15);
    p = addABR(p,20);
    p = addABR(p,12);
    p = addABR(p,7);
    p = addABR(p,45);
    p = addABR(p,9);
    //affichage arbre



    displayInfixe(p);
    printf("\n");

    int*  pElt = NULL;
    printf( "%d \n", isABR(p, &pElt) );

    int Noeud = 0;
    printf("13 est il dans l'abr ? : %d",isInABR(p, 13,&Noeud));
    printf(" nbr Noeud parcouru %d",Noeud);
    printf("\n");

    Noeud = 0;
    printf("12 est il dans l'abr ? : %d",isInABR(p, 12,&Noeud));
    printf(" nbr Noeud parcouru %d",Noeud);
    printf("\n");

    delABR(p,15);

    printf("\n");
    displayInfixe(p);

    pElt = NULL;
    printf( "%d \n", isABR(p, &pElt) );

    return 0;
}










