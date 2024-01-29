#ifndef _AVLCOMMON_H
#define _AVLCOMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL_Int.h"
#include "AVL_Driver.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define OFF_LEFT_CHILD 0
#define OFF_RIGHT_CHILD 8
#define OFF_VALUE 16
#define OFF_BFACTOR 24

// In : Pointer
// Out : int (read as bool)
// Returns 1 if pointer is invalid
int checkPtr(void *ptr);

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
void *avlRotationL(void *pTree);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
void *avlRotationR(void *pTree);

// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
void *avlRotationRL(void *pTree);


// In : Pointer to root of rotation
// Out : Modified root subtree
// Explicit
void *avlRotationLR(void *pTree);


// In : Pointer to Avl to balance
// Out : Pointer to modified Avl
// Rebalances an Avl
void *balanceAvl(void *pTree);


#endif