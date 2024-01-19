#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _avl_str {
    char * name;
    //Avl_int trajet;
    int equilibre;
    struct _avl_str* pL;
    struct _avl_str* pR;
} Avl_str;

Avl_str * createAvl_str(char* chaine){
    Avl_str* pNew = malloc(sizeof(Avl_str));
    if(pNew == NULL){
        exit(1);
    }
    pNew->name = chaine;
    pNew->equilibre = 0;
    pNew->pL    = NULL;
    pNew->pR    = NULL;
    return pNew;
} 
int Avl_str_NULL(Avl_str* pTree){
    return pTree == NULL;
}

int Avl_str_LeftExist(Avl_str * pTree){
    return !Avl_str_NULL(pTree) && !Avl_str_NULL(pTree->pL);
}

int Avl_str_RightExist(Avl_str * pTree){
    return !Avl_str_NULL(pTree) && !Avl_str_NULL(pTree->pR);
}

#define MAX(a,b) (((a)>(b))?(a):(b)) //fct max

int high(Avl_str * pTree){ //hauteur
    int comptL=0,comptR=0;
    if(pTree==NULL){
        return 0;
    }
    if(!Avl_str_LeftExist(pTree) && !Avl_str_LeftExist(pTree)){
        return 1;
    }
    else{
        if(Avl_str_LeftExist(pTree)){
            comptL = high(pTree->pL);
        }
        if(Avl_str_RightExist(pTree)){
            comptR = high(pTree->pR); 
        }
    }
    return MAX(comptL,comptR)+1;
}

Avl_str * equilibrage_str(Avl_str * pTree);

Avl_str * addAvl_str(Avl_str* pTree, char * chaine,int *h){
    if(pTree == NULL){
        // found the place to create new node
        *h = 1;
        return createAvl_str(chaine);
    }
    else if(strcmp(pTree->name,chaine)>0){
        // look into the left subtree
        pTree->pL = addAvl_str(pTree->pL, chaine,h);
        *h = -*h;
    }
    else if(strcmp(pTree->name,chaine)<0){
        // look into the right subtree
        //h reste le mm
        pTree->pR = addAvl_str(pTree->pR, chaine,h);
    }
    else{
        *h = 0;
        return pTree;
        // We have found the same value : do nothing
    }   
    if(*h != 0){
        pTree->equilibre = pTree->equilibre+*h;
        pTree = equilibrage_str(pTree);
        if(pTree->equilibre==0){
            *h = 0;
        }
        else{
            *h = -1;
        }
    }
    return pTree;
}

Avl_str* SuppMax_str(Avl_str* pTree, char ** chaine);

Avl_str* delABR_str(Avl_str * pTree, char * chaine,int *h){
    // element non présent dans l’arbre
    if(pTree == NULL){
        *h = 1;
        return pTree;
    }
    // parcours récursif de l’arbre
    else if(strcmp(pTree->name,chaine)<0){           //go a droite car elem plus grand
        pTree->pR = delABR_str(pTree->pR,chaine,h);
    }
    else if(strcmp(pTree->name,chaine)>0){           //go a gauche car elem plus ptit
        pTree->pL = delABR_str(pTree->pL,chaine,h);
        *h =-*h;
    }
    // élément trouvé : remplacement par fils unique
    else if (!Avl_str_LeftExist(pTree)){ //si il a pas de sous arbre gauche on remplace par sous arbre droit (fils unique)
        Avl_str* tmp;
        tmp = pTree;
        pTree = pTree->pR;
        free(tmp);
        *h = -1;
    }
    // élément trouvé : remplacement par prédécesseur
    else{
        pTree->pL = SuppMax_str(pTree->pL, &(pTree->name));
    }
    if(*h != 0){
        pTree->equilibre = pTree->equilibre+*h;
        pTree = equilibrage_str(pTree);
        if(pTree->equilibre==0){
            *h = 0;
        }
        else{
            *h = -1;
        }
    }
    return pTree;
}

Avl_str* SuppMax_str(Avl_str* pTree, char ** chaine){
    Avl_str * tmp;
    if(Avl_str_RightExist(pTree)){
        SuppMax_str(pTree->pR,chaine);
    }
    else{
        *chaine = pTree->name;
        tmp = pTree;
        pTree = pTree->pL;
        free(tmp);
    }
    return pTree;
}

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Avl_str * Rota_G(Avl_str * pTree){
    if(pTree==NULL||pTree->pR == NULL){
        return 0;
    }
    Avl_str * Pivot = pTree->pR;
    
    pTree->pR = Pivot->pL;
    Pivot->pL = pTree;
    
    //verif equilibrage
    int eq_Ptree = pTree->equilibre, eq_Pivot = Pivot->equilibre;
    pTree->equilibre -= max(eq_Pivot,0) - 1; 
    Pivot->equilibre = min(eq_Ptree + eq_Pivot - 2,min(eq_Ptree - 2,eq_Pivot-1));
    
    pTree = Pivot;
    return pTree;    
}

Avl_str * Rota_D(Avl_str * pTree){
    if(pTree==NULL||pTree->pL == NULL){
        return 0;
    }
    Avl_str * Pivot = pTree->pL;
    pTree ->pL = Pivot->pR;
    Pivot->pR = pTree;
    
    //verif equilibrage
    int eq_Ptree = pTree->equilibre, eq_Pivot = Pivot->equilibre;
    pTree->equilibre -= min(eq_Pivot,0) + 1; 
    Pivot->equilibre = max(eq_Ptree + eq_Pivot + 2,max(eq_Ptree + 2,eq_Pivot+1));
    
    pTree = Pivot;
    return pTree;    
}

Avl_str * RotaDouble_G(Avl_str * pTree){
    if(pTree==NULL){
        return 0;
    }
    pTree->pR = Rota_D(pTree->pR);
    return Rota_G(pTree);
}

Avl_str * RotaDouble_D(Avl_str * pTree){
    if(pTree==NULL){
        return 0;
    }
    pTree->pL = Rota_G(pTree->pL);
    return Rota_D(pTree);
}

Avl_str * equilibrage_str(Avl_str * pTree){
    if(pTree==NULL){
        return pTree;
    }
    else if(pTree->equilibre >=2){
        if(pTree->pR==NULL){
            exit(1);
        }
        if(pTree->pR->equilibre >= 0){
            return Rota_G(pTree);
        }
        else{
            return RotaDouble_G(pTree);
        }
    }
    else if(pTree->equilibre <=-2){
        if(pTree->pL==NULL){
            exit(1);
        }
        if(pTree->pL->equilibre <= 0){
            return Rota_D(pTree);
        }
        else{
            return RotaDouble_D(pTree);
        }
    }
    return pTree;
}

void displayInfixe(Avl_str* p){
    if(p !=NULL){
        displayInfixe(p->pL);
        printf("%s",p->name);
        displayInfixe(p->pR);
    }
}
