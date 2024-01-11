#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node{
    int value;
    struct _node* pNext;
} Node;

Node* creaNode(int a){
    Node* pNew = malloc(sizeof(Node));
    if(pNew == NULL){
        exit(1);
    }
    pNew->value = a;
    pNew->pNext = NULL;
    return pNew;
}

Node* insertHead(Node* pHead,int a){
    Node* pNew = creaNode(a);
    pNew->pNext = pHead;
    return pNew;	
}

void displayList(Node* pHead){
     printf("Liste :");
     while(pHead !=NULL){
        printf("[%d]",pHead->value);
        pHead = pHead->pNext;
        if(pHead != NULL){
            printf("->");
        }
    }
    printf("\n");
}

Node* suprFirst(Node* pHead,int v){
    Node* pTemp=pHead;
    if(pHead==NULL){
        return pHead;
    }
    else if(pHead->value==v){
        return pHead->pNext;
    }
    while(pTemp->pNext != NULL && pTemp->pNext->value != v){
        pTemp = pTemp->pNext;
    }
    if(pTemp->pNext->value == v){
        pTemp->pNext=pTemp->pNext->pNext;
    }
    return pHead;
}


Node* suprAll(Node* pHead,int v){
    Node* pTemp=pHead;
    if(pHead==NULL){
        return pHead;
    }
    else if(pHead->value==v){
        pHead = pHead->pNext;
    }
    while(pTemp->pNext!=NULL){
        if(pTemp->pNext->value == v){
            pTemp->pNext = pTemp->pNext->pNext;
        }
        else{
            pTemp = pTemp->pNext;
        }
    }
    return pHead;
}

int main(){
    Node* pList = NULL;
    srand(2);
    int i,val;
    for(i=0;i<10;i++){
        val = rand()%6;
        pList = insertHead(pList,val);
    }
    displayList(pList);
    pList=suprFirst(pList,3);
    pList=suprAll(pList,3);
    displayList(pList);
    return 0;
}