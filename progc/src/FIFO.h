#ifndef _FIFO_H
#define _FIFO_H

#include "AVL/AVL_Driver.h"

typedef struct _Fifo{
    struct _Fifo* pNext;
    AvlDriver * driver;
}FIFO;


FIFO* creaFIFO(AvlDriver* driver);


FIFO* insertFIFO (FIFO* pHead, AvlDriver* driver);


AvlDriver* suprFIFO(FIFO* pHead);


#endif