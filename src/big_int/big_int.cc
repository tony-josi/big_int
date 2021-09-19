/** 
 *  @file   big_int.cc
 *  @brief  Main source file for the big int library
 *
 *  This file contains the source code the DS used as the big in library
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include "../inc/big_int.hpp"

#define         DEBUG_LOG       (1)
#define         MAX_VERBOSE     (3)     /* Verbose level 3 - max,  1 - min */

#if DEBUG_LOG

    #include <stdio.h>
    #define         _BI_LOG(_VERB, __str__, ...)    do {    \
        if(_VERB <= MAX_VERBOSE) {                          \
            printf("\t==> BI_LOG: ");                       \
            printf(__str__, ##__VA_ARGS__);                 \
            printf("\n");                                   \
        }                                                   \
        else {}                                             \
    } while(0)

#elif   /* DEBUG_LOG */

    #define         _BI_LOG(_VERB, __str__, ...)

#endif  /* DEBUG_LOG */

bi::big_int::big_int() {

    _data           = new BI_BASE_TYPE(DEFAULT_MEM_ALLOC_BYTES);
    _total_data     = DEFAULT_MEM_ALLOC_BYTES / sizeof(BI_BASE_TYPE);
    _top            = 0;
    _neg            = false;

    if(_data)
        _BI_LOG(1, "Big int init, with: %d items", _total_data);
    else
        _BI_LOG(1, "Init failed");
}

bi::big_int::~big_int() {

    delete[]    _data;
    
    _BI_LOG(1, "Freeing: %d, items", _total_data);

}

