#include "AVL_Common.h"

BasicAvlInt* init_BasicAvlInt(){
  BasicAvlInt *pNew = malloc(sizeof(BasicAvlInt));
  if (CHECK_PTR(pNew)) exit(1);

  pNew->h = 0;
  pNew->pRoot = NULL;

  return pNew;
}

 
Driver* create_Driver(char* name, int bool_AvlPath, int id_Path){
    if(CHECK_PTR(name)) exit(4);

    Driver* pNew = malloc(sizeof(Driver));
    if(CHECK_PTR(pNew)) exit(5);

    pNew->name = name;
    pNew->nPath = 1;
    if(bool_AvlPath){
        pNew->AvlPath = init_AvlInt();
        add_AvlInt(pNew->AvlPath, id_Path);
    }
    else{
        pNew->AvlPath = NULL;
    }

}

void free_Driver(Driver* pDriver);

Town* create_Town();
void free_Town(Town* pTown);

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