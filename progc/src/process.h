#ifndef PROCESS_H
#define PROCESS_H

#define ROUTE_ID 0
#define STEP_ID 1
#define TOWN_A 2
#define TOWN_B 3
#define DISTANCE 4
#define NAME 5

#include <stdlib.h>
#include <stdio.h>

#include "FIFO.h"
#include "AVL/AVL_Common.h"




typedef struct{
    long route_ID;
    int step_ID;
    char town_A[50];
    char town_B[50];
    double distance;
    char name[50];

}DataLine;


DataLine* init_ReadLine(FILE* fFile);
int readLine(FILE* fFile, DataLine* pLine);
// Return 0 if the end of the file is reached
// and 1 if not


#endif
