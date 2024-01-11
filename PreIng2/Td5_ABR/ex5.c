#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct _treeb {
    int value;
    struct _treeb *pLeft;
    struct _treeb *pRight;
}Treeb;

typedef struct _fifo{
    Treeb * pVal;
    struct _fifo * pNext;
}FIFO;

Treeb * createTreeb(int val){
    Treeb * New_Tree = malloc(sizeof(Treeb));
    if(New_Tree == NULL){
        exit(1);
    }
    New_Tree->value = val;
    New_Tree->pLeft = NULL;
    New_Tree->pRight = NULL;
    return New_Tree;
}

int TreebNULL(Treeb * pTree){
    return pTree == NULL;
}

int TreeLeaf(Treeb * pTree){
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

int element(Treeb *pTree){
    if(pTree == NULL){
        exit(2);
    }
    if(TreebNULL(pTree)){
        return 0;
    }
    else{
        return pTree->value;

    }
}

int TreebLeftExist(Treeb * pTree){
    return !TreebNULL(pTree) && !TreebNULL(pTree->pLeft);
}

int TreebRightExist(Treeb * pTree){
    return !TreebNULL(pTree) && !TreebNULL(pTree->pRight);
}

Treeb * AddTreeLeft(Treeb * pTree,int val){
    if(pTree == NULL){
        exit(2);
    }
    else if(TreebLeftExist(pTree)){
        exit(3);
    }
    else{
        Treeb * New_Tree = malloc(sizeof(Treeb));
        if(New_Tree == NULL){
            exit(4);
        }
        New_Tree = createTreeb(val);
        pTree->pLeft = New_Tree;
        return pTree;
    }
}

Treeb * AddTreeRight(Treeb * pTree,int val){
    if(pTree == NULL){
        exit(2);
    }
    else if(TreebRightExist(pTree)){
        exit(3);
    }
    else{
        Treeb * New_Tree = malloc(sizeof(Treeb));
        if(New_Tree == NULL){
            exit(4);
        }
        New_Tree = createTreeb(val);
        pTree->pRight = New_Tree;
        return pTree;
    }
}

int NodeShow(Treeb * pTree){
    if(pTree == NULL){
        exit(2);
    }
    if(TreebNULL(pTree)){
        exit(2);
    }
    else{
        printf("%d ",pTree->value);
        return pTree->value;
    }
}
void walkthrough_prefixe(Treeb * pTree){
    if(!TreebNULL(pTree)){
        NodeShow(pTree);
        printf("\n");
        if(TreebLeftExist(pTree)){
            walkthrough_prefixe(pTree->pLeft);
        }
        if(TreebRightExist(pTree)){
            walkthrough_prefixe(pTree->pRight);
        }
    }
}

void walkthrough_postfixe(Treeb * pTree){
    if(!TreebNULL(pTree)){
        if(TreebLeftExist(pTree)){
            walkthrough_postfixe(pTree->pLeft);
        }
        if(TreebRightExist(pTree)){
            walkthrough_postfixe(pTree->pRight);
        }
        NodeShow(pTree);
        printf("\n");
    }
}


typedef struct _tree {
    int value;
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

Tree* creaBin_ABR (Tree* p,Treeb* pb){ //infixe
    if(pb == NULL){
        return p;
    }
    else{
        p = addABR(p,pb->value);
        if(TreebLeftExist(pb)){
            p= creaBin_ABR(p,pb->pLeft);
        }
        if(TreebRightExist(pb)){
            p= creaBin_ABR(p,pb->pRight);
        }
        return p;    
    }
}

void displayInfixe(Tree* p){
    if(p !=NULL){
        displayInfixe(p->pL);
        printf("[%3d]\n",p->value);
        displayInfixe(p->pR);
    }
}

int main(){
    printf("test 1");
    Treeb * pTreeb = malloc(sizeof(Treeb));
    if(pTreeb == NULL){
        exit(2);
    }
    printf("test 2");
    pTreeb = createTreeb(1);
    //rang1
    AddTreeLeft(pTreeb,2);
    AddTreeRight(pTreeb,8);
    //rang2 
    AddTreeLeft(pTreeb->pLeft,3);
    AddTreeRight(pTreeb->pLeft,6);
    AddTreeLeft(pTreeb->pRight,9);
    AddTreeRight(pTreeb->pRight,10);
    //rang3
    AddTreeLeft(pTreeb->pLeft->pLeft,4);
    AddTreeRight(pTreeb->pLeft->pLeft,5);
    AddTreeRight(pTreeb->pLeft->pRight,7);


    Tree * pTree = NULL;
    pTree = creaBin_ABR (pTree,pTreeb);
    displayInfixe(pTree);
    return 0;
}