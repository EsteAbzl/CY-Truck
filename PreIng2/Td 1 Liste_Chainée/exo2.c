#include <stdio.h>
#include <stdlib.h>

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


Node* insertSmort(Node* pHead,int a){
    Node* p1 = pHead;
    Node* pTemp = NULL;
    Node* pNew = creaNode(a);
    if(pHead == NULL){
        return creaNode(a);
    }
    else if(pHead->value>=a){
        return insertHead(pHead,a);
    }
    else{
        while((p1!=NULL)&&(p1->value<pNew->value)){
            pTemp = p1;
            p1 = p1->pNext;
        }
        pTemp->pNext = pNew;
        pNew->pNext = p1;
        return pHead;
    }
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



int main(){
    Node* pList = NULL;
    pList = insertSmort(pList,2);
    displayList(pList);
    pList = insertSmort(pList,1);
    displayList(pList);
    pList = insertSmort(pList,4);
    displayList(pList);
    pList = insertSmort(pList,3);
    displayList(pList);
    return 0;
}
