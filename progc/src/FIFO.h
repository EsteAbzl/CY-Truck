#ifndef _FIFO_H
#define _FIFO_H

// INCLUDES
    #include <stdio.h>
    #include <stdlib.h>

// STRUCTURES
    typedef struct _fifo{
        float val;
        struct _fifo* pNext;
    }FIFO;

// PROTOTYPES
    FIFO* createFIFO(float v);
    void displayFIFO(FIFO *pHead);
    FIFO* addFIFO(FIFO* pHead, float v);
    FIFO* delFIFO(FIFO* pHead);

#endif