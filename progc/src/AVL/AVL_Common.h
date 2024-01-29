#ifndef _AVLCOMMON_H
#define _AVLCOMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../FIFO.h"
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


#endif