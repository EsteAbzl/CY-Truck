#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Avl_Driver.c"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


// Driver AVL node
typedef struct _AvlDriver {
  char *name;             // We use strings as our sort value.
                          // See : man strcmp
  AvlInt *avlPath;        // AvlInt stores every route taken by
                          // the driver.
  float totalDist;        // Explicit
  int nPath;              // Number of routes stored in avlPath
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
int checkLeftAVL(void *ptr);


// In : Pointer to BST
// Out : int (read as bool)
// Checks if right child exists
int checkRightAVL(void *ptr);


// In : Pointer to BST
// Out : int
// Returns height of a BST
int bstHeight(void *ptr);


// In : Pointer to AVL, String
// Out : Pointer to modified AVL
// Adds in a new node to a BST. If the BST is an AVL,
// it will remain balanced.
AvlDriver *addAvlDriver(AvlDriver *pTree, char *str);


// In : Pointer to AVl, String
// Out : Pointer to modified AVL
// Deletes the specified element from the tree.
AvlDriver *delAvlDriver(AvlDriver *pTree, char *str);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *avlRotationL(AvlDriver *pTree);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *avlRotationR(AvlDriver *pTree);

// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *avlRotationRL(AvlDriver *pTree);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
AvlDriver *avlRotationLR(AvlDriver *pTree);


// In : Pointer to AVL to balance
// Out : Pointer to modified AVL
// Rebalances an AVL
AvlDriver *balanceAvlDriver(AvlDriver *pTree);