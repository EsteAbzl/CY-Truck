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
} LIFO;


Node* createNode(int v){
	Node* pNew = malloc(sizeof(Node));
	if(pNew==NULL){
		exit(1);
	}
	pNew->value=v;
	pNew->pNext=NULL;
	return pNew;
}


LIFO* createLifo(){
	LIFO* pLifo = malloc(sizeof(LIFO));
	if(pLifo == NULL){
		exit(5);
	}
	pLifo -> pHead = NULL;
	pLifo ->size = 0;
	return pLifo;	
}

void displayList(Node *pHead){
	while(pHead != NULL){
		printf("[%02d]", pHead->value);
		pHead=pHead->pNext;
	}
	printf("\n");
}

void displayLifo(LIFO *pLifo){
	if(pLifo == NULL){
		exit(6);
	}
	printf("LIFO size = %d\n", pLifo -> size);
	displayList(pLifo ->pHead);
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


void pushLifo(LIFO* pLifo, int v){
	if(pLifo == NULL){
		exit(7);
	}
	pLifo -> pHead = addStart(pLifo ->pHead, v);
	pLifo -> size++;
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

void popLifo(LIFO* pLifo, int* v){
	if(pLifo == NULL){
		exit(8);
	}
	if(pLifo->pHead == NULL){
		exit(9);
	}
	if(v==NULL){
		exit(10);
	}
	*v = pLifo->pHead->value;
	pLifo->pHead = removeNode(pLifo->pHead);
	pLifo->size --;
}	

void separation(LIFO* pLifo,LIFO* pPair,LIFO* pImpair){
	int val;
	if(pLifo == NULL){
		exit(11);
	}
	if(pPair == NULL){
		exit(12);
	}
	if(pImpair == NULL){
		exit(13);
	}
	while(pLifo->pHead != NULL){
		if(pLifo->pHead->value%2 ==0){
			popLifo(pLifo,&val);
			pushLifo(pPair,val);
		}
		else{
			popLifo(pLifo,&val);
			pushLifo(pImpair,val);
		}
	}
}

int main(){
	int val;
	LIFO* pLifo = createLifo();
	if(pLifo == NULL){
		exit(1);
	}
	srand(time(NULL));
	for(int i=0; i<10; i++){
		pushLifo(pLifo, rand()%21);
		displayLifo(pLifo);
	}
	popLifo(pLifo,&val);
	printf("nous avons retire le %d\n",val);
	displayLifo(pLifo);

	LIFO* pPair = createLifo();
	LIFO* pImpair = createLifo();
	separation(pLifo,pPair,pImpair);
	displayLifo(pPair);
	displayLifo(pImpair);

	return 0;
}	
