#include "FIFO.h"

FIFO* createFIFO(float v){
    FIFO* pFifo = malloc(sizeof(FIFO));
    if(pFifo == NULL){
        exit(5);
    }
    pFifo->pNext = NULL;
    pFifo->val = v;
    return pFifo;    
}

void displayFIFO(FIFO *pHead){
    while(pHead != NULL){
        printf("%f", pHead->val);
        pHead=pHead->pNext;
    }
    printf("\n");
}

FIFO* addFIFO(FIFO* pHead, float v){
    FIFO* pNew = createFIFO(v);
    if(pNew==NULL){
        exit(2); //or printf to see the error
    }
    if(pHead == NULL){
      return pNew;
    }
    else{
        FIFO* pTemp = pHead;
        while(pTemp->pNext!=NULL){
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = pNew;
        return pHead;
    }
    return pNew;
}

FIFO* delFIFO(FIFO* pHead){
    FIFO * pTemp = pHead;
    if(pHead==NULL){
        return NULL;
    }
    else{
        pTemp = pHead;
        pHead = pHead->pNext;
        free(pTemp);
    }
    return pHead;
}