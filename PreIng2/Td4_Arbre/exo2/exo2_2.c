#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
    echo $? pour voir code d'exit:

    exit(1) -> malloc raté pour Tree (lors de la CreateTree)
    exit(2) -> le pTree inséré est null
    exit(3) -> un fils gauche/droit est deja présent
    exit(4) -> malloc raté sur le nouv elem (ds fct addLeft / addRight)

*/


typedef struct _tree {
    int value;
    struct _tree *pLeft;
    struct _tree *pRight;
}Tree;

typedef struct _fifo{
    Tree * pVal;
    struct _fifo * pNext;
}FIFO;

Tree * createTree(int val){
    Tree * New_Tree = malloc(sizeof(Tree));
    if(New_Tree == NULL){
        exit(1);
    }
    New_Tree->value = val;
    New_Tree->pLeft = NULL;
    New_Tree->pRight = NULL;
    return New_Tree;
}

int TreeNULL(Tree * pTree){
    return pTree == NULL;
}

int TreeLeaf(Tree * pTree){
    if(pTree == NULL){
        exit(2);
    }
    else if(pTree->pLeft != NULL || pTree->pLeft != NULL ){
        return 0;
    }
    else{
        return 1;
    }
}

int element(Tree *pTree){
    if(pTree == NULL){
        exit(2);
    }
    if(TreeNULL(pTree)){
        return 0;
    }
    else{
        return pTree->value;

    }
}

int TreeLeftExist(Tree * pTree){
    return !TreeNULL(pTree) && !TreeNULL(pTree->pLeft);
}

int TreeRightExist(Tree * pTree){
    return !TreeNULL(pTree) && !TreeNULL(pTree->pRight);
}

Tree * AddTreeLeft(Tree * pTree,int val){
    if(pTree == NULL){
        exit(2);
    }
    else if(TreeLeftExist(pTree)){
        exit(3);
    }
    else{
        Tree * New_Tree = malloc(sizeof(Tree));
        if(New_Tree == NULL){
            exit(4);
        }
        New_Tree = createTree(val);
        pTree->pLeft = New_Tree;
        return pTree;
    }
}

Tree * AddTreeRight(Tree * pTree,int val){
    if(pTree == NULL){
        exit(2);
    }
    else if(TreeRightExist(pTree)){
        exit(3);
    }
    else{
        Tree * New_Tree = malloc(sizeof(Tree));
        if(New_Tree == NULL){
            exit(4);
        }
        New_Tree = createTree(val);
        pTree->pRight = New_Tree;
        return pTree;
    }
}


int NodeShow(Tree * pTree){
    if(pTree == NULL){
        exit(2);
    }
    if(TreeNULL(pTree)){
        exit(2);
    }
    else{
        printf("%d ",pTree->value);
        return pTree->value;
    }
}
void walkthrough_prefixe(Tree * pTree){
    if(!TreeNULL(pTree)){
        NodeShow(pTree);
        printf("\n");
        if(TreeLeftExist(pTree)){
            walkthrough_prefixe(pTree->pLeft);
        }
        if(TreeRightExist(pTree)){
            walkthrough_prefixe(pTree->pRight);
        }
    }
}

void walkthrough_postfixe(Tree * pTree){
    if(!TreeNULL(pTree)){
        if(TreeLeftExist(pTree)){
            walkthrough_postfixe(pTree->pLeft);
        }
        if(TreeRightExist(pTree)){
            walkthrough_postfixe(pTree->pRight);
        }
        NodeShow(pTree);
        printf("\n");
    }
}

/*
void walkthrough_largeur(Tree * pTree){
    Tree * node = malloc(sizeof(Tree))
    FIFO * file = malloc(sizeof(FIFO));
    if(file == NULL || node == NULL){
        exit(5);
    }
    //creer file
    while(!TreeNULL(pTree)){
        //enfiler ds file pTree
        while(file != vide){
            node = defile(file);
            NodeShow(node);
            if(TreeLeftExist(node)){
                enfiler(file,node->pLeft);
            }
            if(TreeRightExist(node)){
                enfiler(file,node->pRight);
            }
        }
    }

}
*/

int modifracine(Tree*pTree,int e){
    if(pTree == NULL){
        exit(2);
    }
    int retour=pTree->value;
    pTree->value = e;
    return retour;
}
void supprfilsR(Tree*pTree); //POUR PRÉCREER LA FCT SUPPRFILSR 

void supprfilsL(Tree*pTree){
    if(pTree==NULL){
        exit(2);
    }
    else if (pTree->pLeft != NULL){
        if(TreeLeftExist(pTree->pLeft)){
            supprfilsL(pTree->pLeft);
        }
        if(TreeRightExist(pTree->pLeft)){
            supprfilsR(pTree->pLeft);
        }
        free(pTree->pLeft);
    }
}

void supprfilsR(Tree*pTree){
    if(pTree==NULL){
        exit(2);
    }
    else if (pTree->pRight != NULL){
        if(TreeLeftExist(pTree->pRight)){
            supprfilsL(pTree->pRight);
        }
        if(TreeRightExist(pTree->pRight)){
            supprfilsR(pTree->pRight);
        }
        free(pTree->pRight);
    }
}

int leaf_count(Tree * pTree){
    int compt=0;
    if(pTree==NULL){
        exit(2);
    }
    if(!TreeLeftExist(pTree) && !TreeLeftExist(pTree)){
        return 1;
    }
    else{
        if(TreeLeftExist(pTree)){
            compt = compt + leaf_count(pTree->pLeft);
        }
        if(TreeRightExist(pTree)){
            compt = compt + leaf_count(pTree->pRight);
        }
    }
    return compt;
}

int node_count(Tree * pTree){
    int compt=1;
    if(pTree==NULL){
        exit(2);
    }
    if(!TreeLeftExist(pTree) && !TreeLeftExist(pTree)){
        return 1;
    }
    else{
        if(TreeLeftExist(pTree)){
            compt = compt + node_count(pTree->pLeft);
        }
        if(TreeRightExist(pTree)){
            compt = compt + node_count(pTree->pRight);
        }
    }
    return compt;
}

#define MAX(a,b) (((a)>(b))?(a):(b)) //fct max

int avlHeight(Tree * pTree){
    int comptL=0,comptR=0;
    if(pTree==NULL){
        exit(2);
    }
    if(!TreeLeftExist(pTree) && !TreeLeftExist(pTree)){
        return 1;
    }
    else{
        if(TreeLeftExist(pTree)){
            comptL = avlHeight(pTree->pLeft);
        }
        if(TreeRightExist(pTree)){
            comptR = avlHeight(pTree->pRight); 
        }
    }
    return MAX(comptL,comptR)+1;
}

int main(){
    Tree * pTree = malloc(sizeof(Tree));
    if(pTree == NULL){
        exit(2);
    }
    pTree = createTree(1);
    //rang1
    AddTreeLeft(pTree,2);
    AddTreeRight(pTree,8);
    //rang2 
    AddTreeLeft(pTree->pLeft,3);
    AddTreeRight(pTree->pLeft,6);
    AddTreeLeft(pTree->pRight,9);
    AddTreeRight(pTree->pRight,10);
    //rang3
    AddTreeLeft(pTree->pLeft->pLeft,4);
    AddTreeRight(pTree->pLeft->pLeft,5);
    AddTreeRight(pTree->pLeft->pRight,7);

    printf("parcours prefixe :\n");
    walkthrough_prefixe(pTree);
    printf("\n");
    printf("parcours postfixe:\n");
    walkthrough_postfixe(pTree);
    
    printf("nbr de feuille = %d\n",leaf_count(pTree));
    printf("nbr de noeud = %d\n",node_count(pTree));
    printf("hauteur = %d\n",avlHeight(pTree));
    return 0;
}
