#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _mode* pNext;
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

void insertEnd(Node* pHead,int a){
    while(pHead->pNext !=NULL){
        pHead = pHead->pNext;
    }
    Node* pNew = creaNode(a);
    pHead->pNext = pNew;
}

void displayList(Node* pHead){
     printf("Liste :");
     while(pHead !=NULL){
        printf("[%02d]",pHead->value);
        pHead = pHead->pNext;
        if(pHead != NULL){
            printf("->");
        }
    }
    printf("\n");
}



int main(){
    printf("veuillez entrer la taille de la liste");
    int taille,compteur=1,tourne=1;
    scanf("%d",&taille);
    Node* pList = NULL;
    pList = insertHead(pList,2);
    compteur++;
    displayList(pList);
    while((compteur<=taille)&&(tourne==1)){
        printf("voulez vous voir la puissance de 2 suivante ? 1 = oui , autre = non");
        scanf("%d",&tourne);
        int a = 1,i;
        if(tourne == 1){
            for(i=0;i<compteur;i++){
                a = a*2;
            }
            insertEnd(pList,a);
            displayList(pList);
            compteur++;
        } 
    }
    return 0;
}
