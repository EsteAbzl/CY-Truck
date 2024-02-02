#ifndef _AVLCOMMON_H
#define _AVLCOMMON_H

// INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "tools.h"
    #include "AVL_BasicInt.h"


// STRUCTURES
    typedef struct Driver{
        char* name;

        // -d1
        int nPath;              // Number of routes stored in AvlPath
        AvlBasicInt* AvlPath;// Record all the path readed
        
        // -d2
        float totalDist;        // Explicit
    }Driver;

    typedef struct Town{
        char* name;
        
        // -t
        int nStartingTown;      
        
        int nPath;                  // Number of routes stored in AvlPath
        AvlBasicInt* AvlPath;    // Record all the path readed

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
    Driver* create_Driver(char* name, int path, float dist);
    Town* create_Town(char* name, int path);
    Route* create_Route(int id, float dist);

    void free_Driver(Driver* pDriver);
    void free_Town(Town* pTown);

#endif