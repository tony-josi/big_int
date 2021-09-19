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

bi::big_int::big_int() {

    _data           = new BI_BASE_TYPE(DEFAULT_MEM_ALLOC_BYTES);
    _total_data     = DEFAULT_MEM_ALLOC_BYTES / sizeof(BI_BASE_TYPE);
    _top            = 0;
    _neg            = false;

}

bi::big_int::~big_int() {

    delete[]    _data;

}

