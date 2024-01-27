#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef struct _node{
	char mot[21];
	struct _node* pNext;
    struct _node* pFront;
} Node;

Node* creaNode(char *str){
    Node *pNew = malloc(sizeof(Node));
    if(pNew == NULL || str == NULL){
        exit(2);
    }
    strcpy(pNew->mot,str); //pour copier la str de carac de str sur pNew->mot
    pNew->pNext = NULL;
    pNew->pFront = NULL;
    return pNew;
}

Node* insertHead(Node* pHead, char *mot){
    Node* pNew = creaNode(mot);
    pNew->pNext = pHead;
    pHead->pFront = pNew;
    return pNew;	
}

void insertEnd(Node* pHead,char *mot){
    while(pHead->pNext !=NULL){
        pHead = pHead->pNext;
    }
    Node* pNew = creaNode(mot);
    pHead->pNext = pNew;
    pNew->pFront = pHead;
}

void displayList(Node* pHead){
     printf("Liste :");
     while(pHead !=NULL){
        printf("%s",pHead->mot);
        pHead = pHead->pNext;
        if(pHead != NULL){
            printf("->");
        }
    }
    printf("\n");
}

void displayInv(Node* pHead){
    printf("Liste :");
    while(pHead->pNext !=NULL){
        pHead = pHead->pNext;
    }
    while(pHead !=NULL){
        printf("%s",pHead->mot);
        pHead = pHead->pFront;
        if(pHead != NULL){
            printf("->");
        }
    }
    printf("\n");
}

int compareMot(char *mot1,char *mot2){
    if(mot1 == NULL || mot2 == NULL){
        exit(3);
    }
    int i=0;
    while(mot1[i] != '\0' || mot2[i] != '\0'){ 
        if(mot1[i]<mot2[i]){
            return 1;
        }
        else if(mot1[i]>mot2[i]){
            return 0;
        }
        else if(mot1[i]==mot2[i]){
            i++;
        }
    }
    return 0; //erreur
}

Node* insertListe(Node* pHead,char *str){
    Node* p1 = pHead;
    Node* pTemp = NULL;
    Node* pNew = creaNode(str);
    if(str == NULL || pNew == NULL){
        exit(1);
    }
    if(pHead == NULL){
        return creaNode(str);
    }
    else if(compareMot(pNew->mot,pHead->mot)){
        return insertHead(pHead,str);
    }
    else{
        while((p1!=NULL)&&compareMot(p1->mot,pNew->mot)){
            pTemp = p1;
            p1 = p1->pNext;
        }
        if(p1==NULL){
            insertEnd(pHead,str);
        }
        else{
            pTemp->pNext = pNew;
            pNew->pFront = pTemp;
            pNew->pNext = p1;
            p1->pFront = pNew;
        }
    }
    return pHead;
}

int main(){
    Node* str1=NULL,*str2=NULL;
    /*
    char str_temp[21]={0}; // \0 indique la fin du string  <- le 0 = '\0'

    printf("veuillez ecrire un mot de 20 carac max");
    scanf("%s",str_temp);
    if(strlen(str_temp)>20){
        exit(1); //dépasse 20 (INTERDIT), strlen cherche \0
    }
    str1 = creaNode(str_temp);

    printf("veuillez ecrire un mot de 20 carac max");
    scanf("%s",str_temp);
    if(strlen(str_temp)>20){
        exit(1); //dépasse 20 (INTERDIT), strlen cherche \0
    }
    str2 = creaNode(str_temp);
    */
    str2=insertListe(str2,"d");
    str2=insertListe(str2,"b");
    str2=insertListe(str2,"a");
    str2=insertListe(str2,"e");
    str2=insertListe(str2,"c");
    str2=insertListe(str2,"f");
    displayList(str2);
    displayInv(str2);

    return 0;
}