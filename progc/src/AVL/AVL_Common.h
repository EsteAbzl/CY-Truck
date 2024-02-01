#ifndef _AVLCOMMON_H
#define _AVLCOMMON_H

// INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "AVL_Char.h"
    #include "AVL_Int.h"

// MACRO
    #ifndef MIN
    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
    #endif

    #ifndef MAX
    #define MAX(a, b) (((a) > (b)) ? (a) : (b))
    #endif

    #ifndef CHECK_PTR
    #define CHECK_PTR(ptr) (ptr == NULL)
    #endif

// DEFINES
    #define OFF_LEFT_CHILD 0    //0x00000
    #define OFF_RIGHT_CHILD 8   //0x01000
    #define OFF_VALUE 16        //0x10000
    #define OFF_BFACTOR 24      //0x11000

// STRUCTURES
    // Defined in AVL_Int.h and AVL_Char.h
    struct _AvlInt;
    struct _AvlChar;

    typedef struct Driver{
        char* name;

        // -d1
        int nPath;              // Number of routes stored in AvlPath
        struct _AvlInt* AvlPath;// Record all the path readed
        
        // -d2
        float totalDist;        // Explicit
    }Driver;

    typedef struct Town{
        char* name;
        
        // -t
        int nStartingTown;      
        
        int nPath;                  // Number of routes stored in AvlPath
        struct _AvlInt* AvlPath;    // Record all the path readed

    }Town;

    typedef struct Route{
        int id;
        
        int nSteps;

        // -l / -s
        float distTot;          // Total Distance
        
        // -s
        float distMin;          // I sincerely hope that these are explicit enough.
        float distMax;
    }Route;

// PROTOTYPES
    Driver* create_Driver();
    void free_Driver(Driver* pDriver);

    Town* create_Town();
    void free_Town(Town* pTown);

    Route* create_Route();
#endif