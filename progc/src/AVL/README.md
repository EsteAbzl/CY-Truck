These files include the necessary AVL-related functions.

To use them, simply ```#include Avl_Common.h``` and it should Just Work<sup>TM</sup>

<sup><sup>Also includes header guards just in case...</sup></sup>

# Structures :
```C
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

// Int AVL node
typedef struct _AvlInt {
  int value;          // Our sorting value is an int
  int bFactor;        // Balance factor
  struct _AvlInt *pL;
  struct _AvlInt *pR;
} AvlInt;
```

# Functions :

Includes rebalancing, manual rotations, sorted addition and deletion of types AvlInt and AvlDriver. AvlDriver uses strings as its sorting value, with the ASCII value of the first non-matching character between two strings as the compaired value.