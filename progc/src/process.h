#ifndef PROCESS_H
#define PROCESS_H

// INCLUDES
    #include <stdlib.h>
    #include <stdio.h>

    
    #include "FIFO.h"
    #include "AVL/AVL_Common.h"
    #include "AVL/AVL_Int.h"
    #include "AVL/AVL_BasicInt.h"
    #include "AVL/AVL_Char.h"
    
    /* old
    #include "AVL/AVL_Route.h"
    #include "AVL/AVL_Town.h"
    #include "AVL/AVL_Driver.h"
    #include "AVL/AVL_TownSteps.h"*/

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

    typedef struct _nodeTop{
        int i_Val;
        float f_Val;
        char c_Val[COLUMN_SIZE];;

        char caption[COLUMN_SIZE];
        
        float f1, f2, f3;
        int i1, i2;

        struct _nodeTop* pNext;
    }NodeTop;

    typedef struct Top{
        int size;

        NodeTop* pFist;
        NodeTop* pLast;
    }Top;

    



// PROTOTYPES
    DataLine* init_ReadLine(FILE* fFile);
    int readLine(FILE* fFile, DataLine* pLine);

    void t_Process(FILE* fFile);
    // Return 0 if the end of the file is reached
    // and 1 if not

/*
    void T_Init(FILE* fData);
    AvlTownsteps* T_Process1(AvlTown* pTown, AvlTownsteps* sortedpTown);
    AvlTown* T_Process2(AvlTownsteps* sortedpTown, AvlTown* targetpTown, int* extract);

    void T2_Init(FILE* fData);
    void T2_Process(AvlTown* pTown);

    void S_Init(FILE* fData);
    void S_Process(AvlRoute* pRoute);

*/
#endif
