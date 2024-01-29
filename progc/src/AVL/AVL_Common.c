#ifndef _AVLCOMMON_C
#define _AVLCOMMON_C

#include "AVL_Common.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int checkPtr(void *ptr) {
  return ptr == NULL;
}


#endif