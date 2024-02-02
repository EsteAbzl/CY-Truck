#ifndef _AVLROUTE_H
#define _AVLROUTE_H

// INCLUDES
    #include "AVL_Common.h"

// STRUCTURES
    // Route Avl node
    typedef struct _AvlRoute {
      struct _AvlRoute *pL;
      struct _AvlRoute *pR;
      int id;           // Sort value.
      
      int bFactor;            // Balance factor
      float distTot;          // Total Distance
      float distMin;          // I sincerely hope that these are explicit enough.
      float distMax;
      float distMaxMin;
      float distAvg;
      int nSteps;
    } AvlRoute;

//PROTOTYPES
    // In : string
    // Out : AvlRoute
    // Creates a new initialized node from an int
    AvlRoute* createAvlRoute(int id);


    // In : Pointer to Avl, Int
    // Out : Pointer to modified Avl
    // Adds in a new node to a BST. If the BST is an Avl,
    // it will remain balanced.
    AvlRoute* addAvlRoute(AvlRoute *pTree, int id);
    // Private ! Do not use !
    AvlRoute* _addAvlRoute(AvlRoute *pTree, int id, int *h);


    // In : Pointer to Avl, Int, Int* with a value of 0
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    AvlRoute* delAvlRoute(AvlRoute *pTree, int *id, int *h);
    AvlRoute* delAvlLargestLong(AvlRoute *pTree, int *id);


    // In : Pointer to Avl, Int
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
