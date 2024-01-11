#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct _node{
	int value;
	struct _node* pNext;
} Node;

typedef struct{
	int size;
	Node* pHead;
} FIFO;

//pour ajouter on fait à la fin (fond queue)
//pour retirer on fait au debut (tete queue)
//on parcours/affiche du debut à la fin

Node* createNode(int v){
	Node* pNew = malloc(sizeof(Node));
	if(pNew==NULL){
		exit(1);
	}
	pNew->value=v;
	pNew->pNext=NULL;
	return pNew;
}


FIFO* createFifo(){
	FIFO* pFifo = malloc(sizeof(FIFO));
	if(pFifo == NULL){
		exit(5);
	}
	pFifo -> pHead = NULL;
	pFifo ->size = 0;
	return pFifo;	
}

void displayList(Node *pHead){
	while(pHead != NULL){
		printf("[%02d]", pHead->value);
		pHead=pHead->pNext;
	}
	printf("\n");
}

void displayFifo(FIFO *pFifo){
	if(pFifo == NULL){
		exit(6);
	}
	printf("FIFO size = %d\n", pFifo -> size);
	displayList(pFifo ->pHead);
	printf("\n");
}

Node* addStart(Node* pHead, int v){
	Node* pNew = createNode(v);
	if(pNew==NULL){
		exit(2); //or printf to see the error
	}
	pNew->pNext = pHead;
	return pNew; //or put pHead=Pnew before that line
}

Node* removeNode(Node* pliste){
	Node* p1=NULL;
	if(pliste==NULL){
		exit(9);
	}
	p1=pliste;
	pliste = pliste->pNext;
	free(p1);
	return pliste;
}		

int main(){
    FIFO* pFifo = createFifo();
	if(pFifo == NULL){
		exit(1);
	}
    return 0;
}
