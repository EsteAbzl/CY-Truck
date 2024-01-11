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

int isfili(Tree * pTree){
    return !(TreeRightExist(pTree)&&TreeLeftExist(pTree));
}

int fctfili(Tree * pTree){
    if(pTree == NULL){
        exit(2);
    }
    if(isfili(pTree)){
        if(TreeLeftExist(pTree)){
            return fctfili(pTree->pLeft);
        }
        else if(TreeRightExist(pTree)) {
            return fctfili(pTree->pRight);
        }
        else{
            return 1;
        }
    }
    else{
        return 0;
    }
}

int isLpeigne(Tree * pTree){
    return (!(TreeRightExist(pTree))&&TreeLeftExist(pTree));
}

Tree * PeigneLCreate(int hauteur){
    int i,val;
    Tree * New_Tree = malloc(sizeof(Tree));
        if(New_Tree == NULL){
            exit(4);
    }
    Tree * Parcour_Tree= New_Tree;
    val = rand()%11;
    New_Tree->value = val;
    for(i=0;i<hauteur-1;i++){
        val = rand()%11;
        AddTreeLeft(Parcour_Tree,val);
        Parcour_Tree = Parcour_Tree->pLeft;        
    }
    return New_Tree;
}

int main(){
    return 0;
}