#ifndef _AVLCOMMON_H
#define _AVLCOMMON_H

#include "Avl_Int.h"
#include "Avl_Driver.h"
#include "Avl_Common.c"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif


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
int avlHeight(void *ptr);


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


// In : Pointer to Avl to balance
// Out : Pointer to modified Avl
// Rebalances an Avl
AvlDriver *balanceAvl(AvlDriver *pTree);


#endif