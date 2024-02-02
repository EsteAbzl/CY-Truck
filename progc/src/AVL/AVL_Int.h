#ifndef _AVLINT_H
#define _AVLINT_H

// INCLUDES
    #include "AVL_Common.h"

// STRUCTURES
    // Int Avl node
    typedef struct _AvlInt {
      struct _AvlInt *pL;
      struct _AvlInt *pR;
      int id;           // Sort value.
      
      int bFactor;            // Balance factor
    } AvlInt;

//PROTOTYPES
    // In : string
    // Out : AvlInt
    // Creates a new initialized node from an int
    AvlInt* createAvlInt(int id);


    // In : Pointer to Avl, Int
    // Out : Pointer to modified Avl
    // Adds in a new node to a BST. If the BST is an Avl,
    // it will remain balanced.
    AvlInt* addAvlInt(AvlInt *pTree, int id);
    // Private ! Do not use !
    AvlInt* _addAvlInt(AvlInt *pTree, int id, int *h);


    // In : Pointer to Avl, Int, Int* with a value of 0
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    AvlInt* delAvlInt(AvlInt *pTree, int *id, int *h);
    AvlInt* delAvlLargestInt(AvlInt *pTree, int *id);


    // In : Pointer to Avl, Int
    // Out : Pointer to found node or NULL if not found
    AvlInt* isInAvlInt(AvlInt *pTree, int id);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlInt(AvlInt *ptr);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlInt(AvlInt *ptr);


    // In : Pointer to BST
    // Out : int
    // Returns height of a BST
    int avlIntHeight(AvlInt *ptr);

    int avlIntSize(AvlInt *ptr);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlInt *avlIntRotationL(AvlInt *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlInt *avlIntRotationR(AvlInt *pTree);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlInt *avlIntRotationRL(AvlInt *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlInt *avlIntRotationLR(AvlInt *pTree);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    AvlInt *balanceAvlInt(AvlInt *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in infixe order
    void inorderInt(AvlInt *pTree);

#endif
