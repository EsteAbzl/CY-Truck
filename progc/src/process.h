#ifndef PROCESS_H
#define PROCESS_H

// INCLUDES
    #include <stdlib.h>
    #include <stdio.h>

    
    #include "FIFO.h"
    #include "AVL/AVL_Common.h"
    #include "AVL/AVL_Route.h"
    #include "AVL/AVL_Town.h"
    #include "AVL/AVL_Driver.h"
// DEFINES
    #define ROUTE_ID 0
    #define STEP_ID 1
    #define TOWN_A 2
    #define TOWN_B 3
    #define DISTANCE 4
    #define NAME 5

    #define COLUMN_SIZE 50

// STRUCTURES
    typedef struct{
        int route_ID;
        int step_ID;
        char town_A[COLUMN_SIZE];
        char town_B[COLUMN_SIZE];
        char name[COLUMN_SIZE];
        double distance;

    }DataLine;

// PROTOTYPES
    DataLine* init_ReadLine(FILE* fFile);
    int readLine(FILE* fFile, DataLine* pLine);
    // Return 0 if the end of the file is reached
    // and 1 if not


    void T_Init(FILE* fData);
    void T_Process(AvlTown* pTown, AvlTown** top10);

    void T2_Init(FILE* fData);

    void S_Init(FILE* fData);
    void S_Process(AvlRoute* pRoute, AvlRoute** top50);

#endif
