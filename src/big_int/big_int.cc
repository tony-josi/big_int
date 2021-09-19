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

#include <stdexcept>
#include <algorithm>

#include "../inc/big_int.hpp"

#define         DEBUG_LOG       (1)

#if DEBUG_LOG

    #include <stdio.h>
    
    #define         _MAX_VERBOSE     (3)     /* Verbose level 3 - max,  1 - min */

    #define         _BI_LOG(_VERB, __str__, ...)    do {    \
        if(_VERB <= _MAX_VERBOSE) {                         \
            printf("\t>>> BI_LOG: ");                       \
            printf(__str__, ##__VA_ARGS__);                 \
            printf("\n");                                   \
        }                                                   \
        else {}                                             \
    } while(0)

#else   /* DEBUG_LOG */

    #define         _BI_LOG(_VERB, __str__, ...)     do {   \
        /* No debug log */                                  \
        } while(0)

#endif  /* DEBUG_LOG */

bi::big_int::big_int() {

    _data           = new BI_BASE_TYPE[DEFAULT_MEM_ALLOC_BYTES / sizeof(BI_BASE_TYPE)];
    _total_data     = DEFAULT_MEM_ALLOC_BYTES / sizeof(BI_BASE_TYPE);
    _top            = 0;
    _neg            = false;

    if(_data) {
        _BI_LOG(1, "Big int init, with: %d items", _total_data);
    } else {
        _BI_LOG(1, "Init failed");
        throw std::length_error("Couldnt find enough memory");
    }
}

int bi::big_int::_big_int_expand(int req) {

    if (req > 0) {
        BI_BASE_TYPE *temp_buff = new BI_BASE_TYPE[_total_data + req];
        if(!temp_buff) {
            _BI_LOG(1, "_big_int_expand failed");
            throw std::length_error("Couldnt find enough memory");
        } else {
            std::copy_n(_data, _total_data, temp_buff);
            delete[] _data;
            _data = temp_buff;
            _total_data += req;
        }
        _BI_LOG(2, "_big_int_expand expanded to total: %d items", _total_data);
        return 0;
    } else {
        _BI_LOG(1, "_big_int_expand fail negetive expand value");
        return -1;
    }

}

int bi::big_int::big_int_string(const std::string &str_num) {

    (void) str_num;
    return 0;

}

bi::big_int::~big_int() {

    delete[]    _data;
    _BI_LOG(1, "Freeing: %d, items", _total_data);

}

