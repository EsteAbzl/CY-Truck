#ifndef _AVLDRIVER_H
#define _AVLDRIVER_H


// Driver Avl node
typedef struct _AvlDriver {
  struct _AvlDriver *pL;
  struct _AvlDriver *pR;
  char *name;             // We use strings as our sort value.
  int bFactor;            // Balance factor
                          // See : man strcmp
  AvlInt *AvlPath;        // AvlInt stores every route taken by
                          // the driver.
  float totalDist;        // Explicit
  int nPath;              // Number of routes stored in AvlPath
} AvlDriver;


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
AvlDriver* delAvlDriver(AvlDriver *pTree, char *str);
// Private ! Do not use !
AvlDriver* _delAvlDriver(AvlDriver *pTree, char *str, int *h);
AvlDriver* delAvlLargestStr(AvlDriver *pTree, char **str);


// In : Pointer to Avl, String
// Out : Pointer to found node or NULL if not found
AvlDriver* isInAvlDriver(AvlDriver *pTree, char *str);


#endif