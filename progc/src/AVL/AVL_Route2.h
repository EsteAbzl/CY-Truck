#ifndef _AVLROUTE2_H
#define _AVLROUTE2_H

// INCLUDES
    #include "AVL_Common.h"

// STRUCTURES
    // Route Avl node
    typedef struct _AvlRoute2 {
      struct _AvlRoute2 *pL;
      struct _AvlRoute2 *pR;
      float distMaxMin;           // Sort value.
      
      float bFactor;            // Balance factor
      float distAvg;          // Total Distance
      float distMin;          // I sincerely hope that these are explicit enough.
      float distMax;
      int id;
    } AvlRoute2;

//PROTOTYPES
    // In : Float
    // Out : AvlRoute2
    // Creates a new initialized node from a float
    AvlRoute2* createAvlRoute2(float id);


    // In : Pointer to Avl, Float
    // Out : Pointer to modified Avl
    // Adds in a new node to a BST. If the BST is an Avl,
    // it will remain balanced.
    AvlRoute2* addAvlRoute2(AvlRoute2 *pTree, float id);
    // Private ! Do not use !
    AvlRoute2* _addAvlRoute2(AvlRoute2 *pTree, float id, float *h);


    // In : Pointer to Avl, Float
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    AvlRoute2* delAvlRoute2(AvlRoute2 *pTree, float *id, float *h);
    AvlRoute2* delAvlLargestFloat(AvlRoute2 *pTree, float *id);


    // In : Pointer to Avl, Float
    // Out : Pointer to found node or NULL if not found
    AvlRoute2* isInAvlRoute2(AvlRoute2 *pTree, float id);


    // In : Pointer to BST
    // Out : float (read as bool)
    // Checks if left child exists
    float checkLeftAvlRoute2(AvlRoute2 *ptr);


    // In : Pointer to BST
    // Out : float (read as bool)
    // Checks if right child exists
    float checkRightAvlRoute2(AvlRoute2 *ptr);


    // In : Pointer to BST
    // Out : float
    // Returns height of a BST
    float avlRoute2Height(AvlRoute2 *ptr);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute2 *avlRoute2RotationL(AvlRoute2 *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute2 *avlRoute2RotationR(AvlRoute2 *pTree);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute2 *avlRoute2RotationRL(AvlRoute2 *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlRoute2 *avlRoute2RotationLR(AvlRoute2 *pTree);


    // In : Pointer to Avl to balance
    // Out : Pofloater to modified Avl
    // Rebalances an Avl
    AvlRoute2 *balanceAvlRoute2(AvlRoute2 *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in inorder order
    void inorderRoute2(AvlRoute2 *pTree, int* i);

    // Fun fact : Since these AVLs are all just copy-pastes of each other, when going through
    // with the auto replace command of my editor, every instance of "Pointer"
    // became "Pofloater". And I think that it's a fun word to say. Pofloater. Pofloater !

#endif
