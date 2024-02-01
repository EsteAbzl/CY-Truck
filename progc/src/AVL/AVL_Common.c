#include "AVL_Common.h"


Driver* create_Driver(char* name, int path, float dist){
    if(CHECK_PTR(name)) exit(4);

    Driver* pNew = malloc(sizeof(Driver));
    if(CHECK_PTR(pNew)) exit(5);

    char* pNewName = malloc(sizeof(char) * strlen(name)+1);
    if(CHECK_PTR(pNewName)) exit(5);
    pNew->name = pNewName;
    strncpy(pNew->name, name, strlen(name));

    pNew->nPath = 1;
    pNew->AvlPath = init_AvlBasicInt();
    add_AvlBasicInt(pNew->AvlPath, path);
    
    pNew->totalDist = dist;

    return pNew;
}

Town* create_Town(char* name, int path){
    if(CHECK_PTR(name)) exit(4);

    Town* pNew = malloc(sizeof(Town));
    if(CHECK_PTR(pNew)) exit(5);

    char* pNewName = malloc(sizeof(char) * strlen(name)+1);
    if(CHECK_PTR(pNewName)) exit(5);
    pNew->name = pNewName;
    strncpy(pNew->name, name, strlen(name));

    pNew->nPath = 1;
    pNew->AvlPath = init_AvlBasicInt();
    add_AvlBasicInt(pNew->AvlPath, path);
    
    pNew->nStartingTown = 0;

    return pNew;
}

Route* create_Route(int id, float dist){
    Route* pNew = malloc(sizeof(Route));
    if(CHECK_PTR(pNew)) exit(5);

    pNew->id = id;

    pNew->nSteps = 1;
    pNew->distTot = dist;
    pNew->distMax = dist;
    pNew->distMin = dist;

    return pNew;
}


void free_Driver(Driver* pDriver){
    if(pDriver){
        if(pDriver->name) free(pDriver->name);
        free_AvlBasicInt(pDriver->AvlPath);

        free(pDriver);
    }
}

void free_Town(Town* pTown){
    if(pTown){
        if(pTown->name) free(pTown->name);
        free_AvlBasicInt(pTown->AvlPath);

        free(pTown);
    }
}