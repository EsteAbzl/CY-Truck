#ifndef _AVLBASICINT_H
#define _AVLBASICINT_H

// INCLUDES
    #include "AVL_Common.h"

//PROTOTYPES

    AvlBasicInt* init_AvlBasicInt();
    NodeAvlBasicInt* create_NodeAvlBasicInt(int id);

    void free_SingularNodeAvlBasicInt(NodeAvlBasicInt* pTree);
    void free_NodeAvlBasicInt(NodeAvlBasicInt* pTree);
    void free_AvlBasicInt(AvlBasicInt* pAvl);

    void add_AvlBasicInt(AvlBasicInt *pAvl, int id);
    NodeAvlBasicInt* add_NodeAvlBasicInt(NodeAvlBasicInt *pTree, int id, int *h);

    void del_AvlBasicInt(AvlBasicInt *pAvl, int id);
    NodeAvlBasicInt* del_NodeAvlBasicInt(NodeAvlBasicInt *pTree, int *id, int *h);
    NodeAvlBasicInt* del_AvlLargestInt(NodeAvlBasicInt *pTree, int *id);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    NodeAvlBasicInt* isInAvlBasicInt(NodeAvlBasicInt *pTree, int id);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlBasicInt(NodeAvlBasicInt *ptr);

    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlBasicInt(NodeAvlBasicInt *ptr);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    NodeAvlBasicInt *balanceAvlBasicInt(NodeAvlBasicInt *pTree);

    NodeAvlBasicInt *avlBasicIntRotationL(NodeAvlBasicInt *pTree);
    NodeAvlBasicInt *avlBasicIntRotationR(NodeAvlBasicInt *pTree);
    NodeAvlBasicInt *avlBasicIntRotationRL(NodeAvlBasicInt *pTree);
    NodeAvlBasicInt *avlBasicIntRotationLR(NodeAvlBasicInt *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in infixe order
    void inorderBasicInt(NodeAvlBasicInt *pTree);

#endif
