#ifndef _FIFO_H
#define _FIFO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _fifo{
    float val;
    struct _fifo* pNext;
}FIFO;

FIFO* createFIFO(float v);

void displayFIFO(FIFO *pHead);

FIFO* addFIFO(FIFO* pHead, float v);

FIFO* delFIFO(FIFO* pHead);

#endif