#ifndef _AVLINT_H
#define _AVLINT_H


// Int AVL node
typedef struct _AvlInt {
  struct _AvlInt *pL;
  struct _AvlInt *pR;
  int* value;          // Our sorting value is an int
  int bFactor;        // Balance factor
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
// Private ! Do not use !
AvlInt *_addAvlInt(AvlInt *p, int v, int *h);


// In : Pointer to Avl, String
// Out : Pointer to modified Avl
// Deletes the specified element from the tree.
AvlInt *delAvlInt(AvlInt *pTree, int elem);
// Private ! Do not use !
AvlInt *_delAvlInt(AvlInt *pTree, int elem, int *h);
AvlInt *delAvlLargestInt(AvlInt *pTree, int *elem);


#endif