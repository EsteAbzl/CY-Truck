#ifndef _AVLCOMMON_H
#define _AVLCOMMON_H

// INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

// MACRO
    #ifndef MIN
    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
    #endif

    #ifndef MAX
    #define MAX(a, b) (((a) > (b)) ? (a) : (b))
    #endif

    #ifndef CHECK_PTR
    #define CHECK_PTR(ptr) (ptr == NULL)
    #endif

// DEFINES
    #define OFF_LEFT_CHILD 0    //0x00000
    #define OFF_RIGHT_CHILD 8   //0x01000
    #define OFF_VALUE 16        //0x10000
    #define OFF_BFACTOR 24      //0x11000

#endif