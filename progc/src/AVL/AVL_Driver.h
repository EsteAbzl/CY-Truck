#ifndef _AVLDRIVER_H
#define _AVLDRIVER_H

// STRUCTURES
    // Driver Avl node
    typedef struct _AvlDriver {
      struct _AvlDriver *pL;
      struct _AvlDriver *pR;
      char *name;             // We use strings as our sort value.
                              // See : man strcmp
      int bFactor;            // Balance factor
      float totalDist;        // Explicit
      int nPath;              // Number of routes stored in AvlPath
    } AvlDriver;

// PROTOTYPES
    // In : string
    // Out : AvlDriver
    // Creates a new initialized node from a string
    AvlDriver* createAvlDriver(char *str);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Adds in a new node to a BST. If the BST is an Avl,
    // it will remain balanced.
    AvlDriver* addAvlDriver(AvlDriver *pTree, char *str);
    // Private ! Do not use !
    AvlDriver* _addAvlDriver(AvlDriver *pTree, char *str, int *h);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    //AvlDriver* delAvlDriver(AvlDriver *pTree, char *str);
    // Private ! Do not use !
    AvlDriver* delAvlDriver(AvlDriver *pTree, char *str, int *h);
    AvlDriver* delAvlLargestStr(AvlDriver *pTree, char **str);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    AvlDriver* isInAvlDriver(AvlDriver *pTree, char *str);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if left child exists
    int checkLeftAvlDriver(AvlDriver *ptr);


    // In : Pointer to BST
    // Out : int (read as bool)
    // Checks if right child exists
    int checkRightAvlDriver(AvlDriver *ptr);


    // In : Pointer to BST
    // Out : int
    // Returns height of a BST
    int avlDriverHeight(AvlDriver *ptr);

    int avlDriverNodeCount(AvlDriver *ptr);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlDriver *avlDriverRotationL(AvlDriver *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlDriver *avlDriverRotationR(AvlDriver *pTree);

    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlDriver *avlDriverRotationRL(AvlDriver *pTree);


    // In : Pointer to root of rotation
    // Out : Modified root subtree
    // Explicit
    AvlDriver *avlDriverRotationLR(AvlDriver *pTree);


    // In : Pointer to Avl to balance
    // Out : Pointer to modified Avl
    // Rebalances an Avl
    AvlDriver *balanceAvlDriver(AvlDriver *pTree);

    // In : Pointer to Avl to balance
    // print val of the avl in infixe order
    void infixe(AvlDriver *pTree);

#endif
