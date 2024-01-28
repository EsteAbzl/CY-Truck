#ifndef _AVLDRIVER_H
#define _AVLDRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


// In : Pointer to Avl, String
// Out : Pointer to modified Avl
// Adds in a new node to a BST. If the BST is an Avl,
// it will remain balanced.
AvlDriver *addAvlDriver(AvlDriver *pTree, char *str);


// In : Pointer to Avl, String
// Out : Pointer to modified Avl
// Deletes the specified element from the tree.
AvlDriver *delAvlDriver(AvlDriver *pTree, char *str);

// In : Pointer to Avl, String
// Out : Pointer to searched value or 0 if not found
AvlDriver *isInAvl(AvlDriver *pTree,char *str);


#endif
