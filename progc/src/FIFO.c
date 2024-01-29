#include "FIFO.h"

FIFO* creaFIFO(AvlDriver* driver){
    FIFO *pNew = malloc(sizeof(FIFO));
    if(pNew == NULL || driver == NULL){
        exit(2);
    }
    pNew->driver = driver;
    pNew->pNext = NULL;
    return pNew;
}

FIFO* insertFIFO (FIFO* pHead, AvlDriver* driver){
    if(checkptr(pHead)){
      return creaFIFO(driver);
    }
    else{
      pTemp = pHead;
      while(pTemp->pNext !=NULL){
        pTemp = pTemp->pNext;
      }
      Node* pNew = creaFIFO(driver);
      pTemp->pNext = pNew;
      return pHead;
    }
    return 0;
}

AvlDriver* suprFIFO(FIFO* pHead){
    temp = pHead;
    pHead = pHead->pNext;
    return temp->driver;	
}