#include "AVL_Common.h"

Driver* create_Driver(char* name, int bool_AvlPath, int id_Path){
    if(CHECK_PTR(name)) exit(4);

    Driver* pNew = malloc(sizeof(Driver));
    if(CHECK_PTR(name)) exit(5);

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

Route* create_Route();