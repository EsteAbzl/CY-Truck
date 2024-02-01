#ifndef _AVLTOWNSTEPS_H
#define _AVLTOWNSTEPS_H

// INCLUDES
    #include "AVL_Common.h"

// STRUCTURES
    // Driver Avl node
    typedef struct _AvlTownsteps {
      struct _AvlTownsteps *pL;
      struct _AvlTownsteps *pR;
      int nPass;                // We use ints as our sort value
      int nFirst;              // Times that we were the first town
      char* name;             // Town name
      int bFactor;            // Balance factor
    } AvlTownsteps;

// PROTOTYPES
    // In : string
    // Out : AvlTownsteps
    // Creates a new initialized node from a string
    AvlTownsteps* createAvlTownsteps(int val);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Adds in a new node to a BST. If the BST is an Avl,
    // it will remain balanced.
    AvlTownsteps* addAvlTownsteps(AvlTownsteps *pTree, int val);
    // Private ! Do not use !
    AvlTownsteps* _addAvlTownsteps(AvlTownsteps *pTree, int val, int *h);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    //AvlTownsteps* delAvlTownsteps(AvlTownsteps *pTree, char *str);
    // Private ! Do not use !
    AvlTownsteps* delAvlTownsteps(AvlTownsteps *pTree, int val, int *h);
    AvlTownsteps* delAvlLargestPass(AvlTownsteps *pTree, int* val);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    AvlTownsteps* isInAvlTownsteps(AvlTownsteps *pTree, int val);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlTownsteps(AvlTownsteps *ptr);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlTownsteps(AvlTownsteps *ptr);


    // In : Pointer to BST
    // Out : int
    // Returns height of a BST
    int avlTownstepsHeight(AvlTownsteps *ptr);

    int avlTownstepsNodeCount(AvlTownsteps *ptr);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTownsteps *avlTownstepsRotationL(AvlTownsteps *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTownsteps *avlTownstepsRotationR(AvlTownsteps *pTree);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTownsteps *avlTownstepsRotationRL(AvlTownsteps *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTownsteps *avlTownstepsRotationLR(AvlTownsteps *pTree);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    AvlTownsteps *balanceAvlTownsteps(AvlTownsteps *pTree);

#endif
