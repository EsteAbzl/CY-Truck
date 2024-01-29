#ifndef _FIFO_H
#define _FIFO_H


typedef struct _Fifo{
    struct _Fifo* pNext;
    AvlDriver * driver;
}FIFO;


#endif