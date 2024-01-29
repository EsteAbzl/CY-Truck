
#include "AVL/AVL_Common.h"
#include "FIFO.h"

FIFO* creaFIFO(AvlDriver* driver){
    FIFO *pNew = malloc(sizeof(FIFO));
    if(!checkPtr(pNew) || !checkPtr(driver)){
        exit(2);
    }
    pNew->driver = driver;
    pNew->pNext = NULL;
    return pNew;
}

FIFO* insertFIFO (FIFO* pHead, AvlDriver* driver){
    FIFO* pTemp = NULL;
    if(!checkPtr(pHead)){
      return creaFIFO(driver);
    }
    else{
      pTemp = pHead;
      while(pTemp->pNext !=NULL){
        pTemp = pTemp->pNext;
      }
      FIFO* pNew = creaFIFO(driver);
      pTemp->pNext = pNew;
      return pHead;
    }
    return 0;
}

AvlDriver* suprFIFO(FIFO* pHead){
    FIFO* ptemp = pHead;
    pHead = pHead->pNext;
    return ptemp->driver;	
}