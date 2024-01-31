#ifndef _AVLROUTE_H
#define _AVLROUTE_H

// STRUCTURES
    // Route Avl node
    typedef struct _AvlRoute {
      struct _AvlRoute *pL;
      struct _AvlRoute *pR;
      long id;           // We use a long as our sort value.
                              // This makes no sense, but the guy that coded
                              // ReadLine refused to make route IDs into ints.  \r ^^'
      int bFactor;            // Balance factor
      float distTot;          // Total Distance
      float distMin;          // I sincerely hope that these are explicit enough.
      float distMax;
      int nSteps;
    } AvlRoute;

//PROTOTYPES
    // In : string
    // Out : AvlDriver
    // Creates a new initialized node from a string
    AvlRoute* createAvlRoute(long id);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Adds in a new node to a BST. If the BST is an Avl,
    // it will remain balanced.
    AvlRoute* addAvlRoute(AvlRoute *pTree, long id);
    // Private ! Do not use !
    AvlRoute* _addAvlRoute(AvlRoute *pTree, long id, int *h);


    // In : Pointer to Avl, String
    // Out : Pointer to modified Avl
    // Deletes the specified element from the tree.
    //AvlDriver* delAvlDriver(AvlDriver *pTree, char *str);
    // Private ! Do not use !
    AvlRoute* delAvlRoute(AvlRoute *pTree, long *id, int *h);
    AvlRoute* delAvlLargestLong(AvlRoute *pTree, long *id);


    // In : Pointer to Avl, String
    // Out : Pointer to found node or NULL if not found
    AvlRoute* isInAvlRoute(AvlRoute *pTree, long id);


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
