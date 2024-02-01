#ifndef _AVLROUTE_H
#define _AVLROUTE_H

// INCLUDES
    #include "AVL_Common.h"

// STRUCTURES
    typedef struct _NodeAvlInt{
        int value;           // Sort value.
        // +any struct or value of use

        int bFactor;            // Balance factor

        struct _NodeAvlInt* pL;
        struct _NodeAvlInt* pR;
    }NodeAvlInt;

    typedef struct AvlInt{
        int h;

        NodeAvlInt pRoot;
    }AvlInt;

//PROTOTYPES

    AvlInt init_AvlInt();

    void free_AvlInt(AvlInt* pAvlInt);
    void free_NodeAvlInt(NodeAvlInt* pTree);

    void add_AvlInt(AvlInt pAvlInt, int value);
    NodeAvlInt add_NodeAvlInt(NodeAvlInt pTree, int value, int *h);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    //AvlDriver* delAvlDriver(AvlDriver *pTree, char *str);
    // Private ! Do not use !
    AvlRoute* delAvlRoute(AvlRoute *pTree, int *id, int *h);
    AvlRoute* delAvlLargestLong(AvlRoute *pTree, int *id);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    AvlRoute* isInAvlRoute(AvlRoute *pTree, int id);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlRoute(AvlRoute *ptr);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlRoute(AvlRoute *ptr);


    // In : Pointer to BST
    // Out : int
    // Returns height of a BST
    int avlRouteHeight(AvlRoute *ptr);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute *avlRouteRotationL(AvlRoute *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute *avlRouteRotationR(AvlRoute *pTree);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute *avlRouteRotationRL(AvlRoute *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute *avlRouteRotationLR(AvlRoute *pTree);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    AvlRoute *balanceAvlRoute(AvlRoute *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in infixe order
    void inorderRoute(AvlRoute *pTree);

#endif
