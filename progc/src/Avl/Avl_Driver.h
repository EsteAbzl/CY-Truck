#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Avl_Driver.c"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


// Driver Avl node
typedef struct _AvlDriver {
  char *name;             // We use strings as our sort value.
                          // See : man strcmp
  AvlInt *AvlPath;        // AvlInt stores every route taken by
                          // the driver.
  float totalDist;        // Explicit
  int nPath;              // Number of routes stored in AvlPath
  int bFactor;            // Balance factor
  struct _AvlDriver *pL;
  struct _AvlDriver *pR;
} AvlDriver;


// In : string
// Out : AvlDriver
// Creates a new initialized node from a string
AvlDriver *createAvlDriver(char *str);


// In : Pointer
// Out : int (read as bool)
// Returns 1 if pointer is invalid
int checkPtr(void *ptr) {
  return ptr == NULL;
}


// In : Pointer to BST
// Out : int (read as bool)
// Checks if left child exists
int checkLeftAvl(void *ptr);


// In : Pointer to BST
// Out : int (read as bool)
// Checks if right child exists
int checkRightAvl(void *ptr);


// In : Pointer to BST
// Out : int
// Returns height of a BST
int AvlHeight(void *ptr);


// In : Pointer to Avl, String
// Out : Pointer to modified Avl
// Adds in a new node to a BST. If the BST is an Avl,
// it will remain balanced.
AvlDriver *addAvlDriver(AvlDriver *pTree, char *str);


// In : Pointer to Avl, String
// Out : Pointer to modified Avl
// Deletes the specified element from the tree.
AvlDriver *delAvlDriver(AvlDriver *pTree, char *str);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *AvlRotationL(AvlDriver *pTree);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *AvlRotationR(AvlDriver *pTree);

// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *AvlRotationRL(AvlDriver *pTree);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *AvlRotationLR(AvlDriver *pTree);


// In : Pointer to Avl to balance
// Out : Pointer to modified Avl
// Rebalances an Avl
AvlDriver *balanceAvl(AvlDriver *pTree);