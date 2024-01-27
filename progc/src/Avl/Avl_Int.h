#ifndef _AVLINT_H
#define _AVLINT_H

#include <stdio.h>
#include <stdlib.h>

#include "Avl_Int.c"


// Int AVL node
typedef struct _AvlInt {
  int value;          // Our sorting value is an int
  int bFactor;        // Balance factor
  struct _AvlInt *pL;
  struct _AvlInt *pR;
} AvlInt;


// In : int
// Out : AvlInt
// Creates a new initialized node from an int
AvlInt *createAvlInt(int v);


// In : Pointer to Avl, int
// Out : Pointer to modified Avl
// Adds in a new node to a BST. If the BST is an Avl,
// it will remain balanced.
AvlInt *addAvlInt(AvlInt *pTree, int elem);


// In : Pointer to Avl, String
// Out : Pointer to modified Avl
// Deletes the specified element from the tree.
AvlDriver *delAvlInt(AvlDriver *pTree, char *str);


#endif