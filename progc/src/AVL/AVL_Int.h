#ifndef _AVLROUTE_H
#define _AVLROUTE_H

// INCLUDES
    #include "AVL_Common.h"

// STRUCTURES
    typedef struct _NodeAvlInt{
        int value;           // Sort value.
        Route* pRoute;

        int bFactor;            // Balance factor
        struct _NodeAvlInt* pL;
        struct _NodeAvlInt* pR;
    }NodeAvlInt;

    typedef struct _AvlInt{
        int h;

        NodeAvlInt* pRoot;
    }AvlInt;

//PROTOTYPES

    AvlInt* init_AvlInt();
    //use as follow:
    //1) create_NodeAvlInt(id_route, create_Route(id_route, step_lenth));
    //2) create_NodeAvlInt(id_route, NULL);
    NodeAvlInt* create_NodeAvlInt(int id, Route* pRoute);

    void free_SingularNodeAvlInt(NodeAvlInt* pTree);
    void free_NodeAvlInt(NodeAvlInt* pTree);
    void free_AvlInt(AvlInt* pAvlInt);

    void add_AvlInt(AvlInt *pAvl, Route* pRoute, int id);
    NodeAvlInt* add_NodeAvlInt(NodeAvlInt *pTree, int id, Route* pRoute, int *h);

    void del_AvlInt(AvlInt *pAvl, int id);
    NodeAvlInt* del_NodeAvlInt(NodeAvlInt *pTree, int *id, int *h);
    NodeAvlInt* del_AvlLargestInt(NodeAvlInt *pTree, int *id);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    NodeAvlInt* isInAvlInt(NodeAvlInt *pTree, int id)


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlInt(NodeAvlInt *ptr);

    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlInt(NodeAvlInt *ptr);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    NodeAvlInt *balanceAvlInt(NodeAvlInt *pTree);

    NodeAvlInt *avlIntRotationL(NodeAvlInt *pTree);
    NodeAvlInt *avlIntRotationR(NodeAvlInt *pTree);
    NodeAvlInt *avlIntRotationRL(NodeAvlInt *pTree);
    NodeAvlInt *avlIntRotationLR(NodeAvlInt *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in infixe order
    void inorderInt(NodeAvlInt *pTree);

#endif
