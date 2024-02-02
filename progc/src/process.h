#ifndef PROCESS_H
#define PROCESS_H

// INCLUDES
    #include <stdlib.h>
    #include <stdio.h>

    
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

    typedef struct _nodeTopT{
        int i_Val;
        char c_Val[COLUMN_SIZE];

        char caption[COLUMN_SIZE];
        int nPath, nFirstPath;

        struct _nodeTopT* pNext;
    }NodeTopT;

    typedef struct Top_T{
        int size;

        int i_ValMin;
        char c_ValMin[COLUMN_SIZE];

        NodeTopT* pFist;
    }Top_T;


// PROTOTYPES
    DataLine* init_ReadLine(FILE* fFile);
    int readLine(FILE* fFile, DataLine* pLine);

    void init_Top(Top_T* pTop);
    NodeTopT *create_NodeTopT(NodeAvlChar* pNodeAvlTown);
    void free_NodeTopT(NodeTopT* pNode);
    NodeTopT* insertTopT(NodeTopT* pNode, int val, NodeAvlChar* pNodeAvlTown);
    void popLastTopT(NodeTopT* pNode, int* valMin);
    void compute_t_Top(NodeAvlChar* pTree, Top_T* pTop);
    void print_t_Top(Top_T* pTop);
    void t_Top(AvlChar* pAvlTown);

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
