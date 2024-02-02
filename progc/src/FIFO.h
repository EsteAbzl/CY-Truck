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
    // In : Float
    // Out : FIFO*
    // Creates a FIFO from a float.
    FIFO* createFIFO(float v);


    // In : FIFO*
    // Displays the contents of a FIFO sequencially
    void displayFIFO(FIFO *pHead);


    // In : FIFO*, float
    // Out : modified FIFO*
    // Adds a new element to a provided FIFO
    FIFO* addFIFO(FIFO* pHead, float v);


    // In : FIFO*
    // Out : Modified FIFO*
    // Deletes the first element of a FIFO.
    FIFO* delFIFO(FIFO* pHead);

#endif