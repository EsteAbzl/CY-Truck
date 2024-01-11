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

Node* creaNode(char *chaine){
    Node *pNew = malloc(sizeof(Node));
    if(pNew == NULL || chaine == NULL){
        exit(2);
    }
    strcpy(pNew->mot,chaine); //pour copier la chaine de carac de chaine sur pNew->mot
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

Node* insertListe(Node* pHead,char *chaine){
    Node* p1 = pHead;
    Node* pTemp = NULL;
    Node* pNew = creaNode(chaine);
    if(chaine == NULL || pNew == NULL){
        exit(1);
    }
    if(pHead == NULL){
        return creaNode(chaine);
    }
    else if(compareMot(pNew->mot,pHead->mot)){
        return insertHead(pHead,chaine);
    }
    else{
        while((p1!=NULL)&&compareMot(p1->mot,pNew->mot)){
            pTemp = p1;
            p1 = p1->pNext;
        }
        if(p1==NULL){
            insertEnd(pHead,chaine);
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
    Node* chaine1=NULL,*chaine2=NULL;
    /*
    char chaine_temp[21]={0}; // \0 indique la fin du string  <- le 0 = '\0'

    printf("veuillez ecrire un mot de 20 carac max");
    scanf("%s",chaine_temp);
    if(strlen(chaine_temp)>20){
        exit(1); //dépasse 20 (INTERDIT), strlen cherche \0
    }
    chaine1 = creaNode(chaine_temp);

    printf("veuillez ecrire un mot de 20 carac max");
    scanf("%s",chaine_temp);
    if(strlen(chaine_temp)>20){
        exit(1); //dépasse 20 (INTERDIT), strlen cherche \0
    }
    chaine2 = creaNode(chaine_temp);
    */
    chaine2=insertListe(chaine2,"d");
    chaine2=insertListe(chaine2,"b");
    chaine2=insertListe(chaine2,"a");
    chaine2=insertListe(chaine2,"e");
    chaine2=insertListe(chaine2,"c");
    chaine2=insertListe(chaine2,"f");
    displayList(chaine2);
    displayInv(chaine2);

    return 0;
}