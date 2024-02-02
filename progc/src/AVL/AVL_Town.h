#ifndef _AVLTOWN_H
#define _AVLTOWN_H

// INCLUDES
    #include "AVL_Common.h"
    #include "AVL_Driver.h"
    #include "AVL_Int.h"

// STRUCTURES
    // Driver Avl node
    typedef struct _AvlTown {
      struct _AvlTown *pL;
      struct _AvlTown *pR;
      char *name;             // We use strings as our sort value.
                              // See : man strcmp
      int bFactor;            // Balance factor
      int nPass;              // Number of times a city was driven through
      AvlDriver* pDrivers;    // Drivers that passed throug the town
      int nFirst;             // Times that the town was the first of a route
      AvlInt* pRoutes;
    } AvlTown;

// PROTOTYPES
    // In : string
    // Out : AvlTown
    // Creates a new initialized node from a string
    AvlTown* createAvlTown(char *str);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Adds in a new node to a BST. If the BST is an Avl,
    // it will remain balanced.
    AvlTown* addAvlTown(AvlTown *pTree, char *str);
    // Private ! Do not use !
    AvlTown* _addAvlTown(AvlTown *pTree, char *str, int *h);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    //AvlTown* delAvlTown(AvlTown *pTree, char *str);
    // Private ! Do not use !
    AvlTown* delAvlTown(AvlTown *pTree, char *str, int *h);
    AvlTown* delAvlTownLargestStr(AvlTown *pTree, char **str);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    AvlTown* isInAvlTown(AvlTown *pTree, char *str);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlTown(AvlTown *ptr);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlTown(AvlTown *ptr);


    // In : Pointer to BST
    // Out : int
    // Returns height of a BST
    int avlTownHeight(AvlTown *ptr);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTown *avlTownRotationL(AvlTown *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTown *avlTownRotationR(AvlTown *pTree);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTown *avlTownRotationRL(AvlTown *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlTown *avlTownRotationLR(AvlTown *pTree);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    AvlTown *balanceAvlTown(AvlTown *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in infixe order
    void inorderTown(AvlTown *pTree);

#endif
