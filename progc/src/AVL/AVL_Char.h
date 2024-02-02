#ifndef _AVLCHAR_H
#define _AVLCHAR_H

// INCLUDES
    #include "AVL_Common.h"

// STRUCTURES
    typedef struct _NodeAvlChar{
        char* value;           // Sort value.
        Driver* pDriver;
        Town* pTown;

        int bFactor;            // Balance factor
        struct _NodeAvlChar* pL;
        struct _NodeAvlChar* pR;
    }NodeAvlChar;

    typedef struct _AvlChar{
        int h;

        NodeAvlChar* pRoot;
    }AvlChar;

//PROTOTYPES

    AvlChar* init_AvlChar();
    //use as follow:
    //1) create_NodeAvlChar(name, create_Driver(name, info), NULL);
    //2) create_NodeAvlChar(name, NULL, create_Town(name, info));
    //2) create_NodeAvlChar(name, NULL, NULL);
    NodeAvlChar* create_NodeAvlChar(char* id, Driver* pDriver, Town* pTown);

    void free_SingularNodeAvlChar(NodeAvlChar* pTree);
    void free_NodeAvlChar(NodeAvlChar* pTree);
    void free_AvlChar(AvlChar* pAvl);

    void add_AvlChar(AvlChar *pAvl, Driver* pDriver, Town* pTown, char* id);
    NodeAvlChar* add_NodeAvlChar(NodeAvlChar *pTree, char* id, Driver* pDriver, Town* pTown, int *h);

    void del_AvlChar(AvlChar *pAvl, char* id);
    NodeAvlChar* del_NodeAvlChar(NodeAvlChar *pTree, char* id, int *h);
    NodeAvlChar* del_AvlLargestStr(NodeAvlChar *pTree, char** id);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    NodeAvlChar* isInAvlChar(NodeAvlChar *pTree, char* id);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlChar(NodeAvlChar *ptr);

    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlChar(NodeAvlChar *ptr);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    NodeAvlChar *balanceAvlChar(NodeAvlChar *pTree);

    NodeAvlChar *AvlCharRotationL(NodeAvlChar *pTree);
    NodeAvlChar *AvlCharRotationR(NodeAvlChar *pTree);
    NodeAvlChar *AvlCharRotationRL(NodeAvlChar *pTree);
    NodeAvlChar *AvlCharRotationLR(NodeAvlChar *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in infixe order
    void inorderChar(NodeAvlChar *pTree);

#endif
