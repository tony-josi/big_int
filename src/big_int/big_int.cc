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
#include <string.h>
#include <memory>

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

namespace {

    static int compare_bi_base_type(const BI_BASE_TYPE *a, const BI_BASE_TYPE *b);

}

bi::big_int::big_int() 
:   _total_data {DEFAULT_MEM_ALLOC_BYTES / sizeof(BI_BASE_TYPE)},  
    _top        {0},
    _neg        {false} {

    _data           = new BI_BASE_TYPE[DEFAULT_MEM_ALLOC_BYTES / sizeof(BI_BASE_TYPE)];

    if(_data) {
        _BI_LOG(1, "Big int init, with: %d items", _total_data);
    } else {
        _BI_LOG(1, "Init failed");
        throw std::length_error("Couldnt find enough memory");
    }

    _BI_LOG(3, "Default 'ctor");
}

bi::big_int::big_int(const bi::big_int &src) 
:   _total_data {src._total_data},  
    _top        {src._top},
    _neg        {src._neg} {

    for(int i = 0; i < _top; ++i) {
        _data[i] = src._data[i];
    }

    _BI_LOG(3, "Copy 'ctor");
}

bi::big_int& bi::big_int::operator=(bi::big_int src) {

    _swap_big_int(src);
    return *this;

    _BI_LOG(3, "Copy/Move assign. 'ctor");

}

bi::big_int::big_int(bi::big_int &&src) {

    _swap_big_int(src);

    _BI_LOG(3, "Move 'ctor");

}

bi::big_int::~big_int() {

    delete[]    _data;
    _BI_LOG(1, "Freeing: %d, items", _total_data);

}

void bi::big_int::_swap_big_int(bi::big_int &src) {

    using std::swap;

    swap(_data,         src._data);
    swap(_total_data,   src._total_data);
    swap(_top,          src._top);
    swap(_neg,          src._neg);

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

int bi::big_int::big_int_from_string(const std::string &str_num) {

    /*
    int str_size = static_cast<int>(str_num.length());
    int extr_space_reqd = ((str_size % 9 == 0) ? 0 : (9 - (str_size % 9)));
    int base_t_aligned_size = str_size + extr_space_reqd;
    char *temp_str = new char[static_cast<size_t>(base_t_aligned_size) + 1]; // +1 for NULL
    memset(temp_str, '0', static_cast<size_t>(base_t_aligned_size) + 1);
    memcpy(temp_str + extr_space_reqd, str_num.c_str(), static_cast<size_t>(str_size) + 1);

    for (int i = (base_t_aligned_size / 9) - 1; i >= 0; --i) {
        BI_BASE_TYPE t_val = static_cast<BI_BASE_TYPE>(strtoul(temp_str + static_cast<size_t>(i) * 9, NULL, 10));
        memset(temp_str + static_cast<size_t>(i) * 9, '\0', 9);
        _data[_top++] = t_val;
        if (_top == _total_data) {
            _big_int_expand(32);
        }
    }

    delete[] temp_str;
    return 0;
    */

    size_t str_size = str_num.length();
    size_t extr_space_reqd = ((str_size % BI_HEX_STR_TO_DATA_SIZE == 0) ? \
    0 : (BI_HEX_STR_TO_DATA_SIZE - (str_size % BI_HEX_STR_TO_DATA_SIZE)));
    
    size_t base_t_aligned_size = str_size + extr_space_reqd;
    std::unique_ptr<char []> temp_str(new char[base_t_aligned_size]);
    memset(temp_str.get(), '0', extr_space_reqd);
    memcpy(temp_str.get() + extr_space_reqd, str_num.c_str(), str_size);

    int str_cur_indx = static_cast<int>(base_t_aligned_size - BI_HEX_STR_TO_DATA_SIZE);

    for(; str_cur_indx >= 0; str_cur_indx -= static_cast<int>(BI_HEX_STR_TO_DATA_SIZE)) {
        sscanf(&(temp_str.get()[str_cur_indx]), BI_SSCANF_FORMAT_HEX, &_data[_top++]);
        if(_top == _total_data) {
            _big_int_expand(BI_DEFAULT_EXPAND_COUNT);
        }
    }

    return 0;

}

int bi::big_int::big_int_unsigned_add(const bi::big_int &b) {

    int max_data_len, min_data_len;

    if (_top > b._top) {
        min_data_len = b._top;
        max_data_len = _top;
    } else {
        min_data_len = _top;
        max_data_len = b._top;
    }

    int i;

    BI_DOUBLE_BASE_TYPE sum = 0;
    BI_BASE_TYPE carry = 0;
    for(i = 0; i < min_data_len; ++i) {
        sum = b._data[i] + _data[i] + carry;
        carry = (sum & ~0xFFFFFFFF) >> 32;
        _data[i] = sum & 0xFFFFFFFF;
    }
    int top_cntr = 0;
    for(; i < max_data_len; ++i) {
        if(i >= _total_data) {
            _big_int_expand(BI_DEFAULT_EXPAND_COUNT);
        }
        if(i >= _top) {
            ++top_cntr;
        }
        if(i < _top) {
            sum = _data[i] + carry;
        } else {
            sum = b._data[i] + carry;
        }
        carry = (sum & ~0xFFFFFFFF) >> 32;
        _data[i] = sum & 0xFFFFFFFF;
    }
    _top += top_cntr;
    return 0;

}

int bi::big_int::big_int_unsigned_add(const bi::big_int &b, bi::big_int *res) {

    res->big_int_clear();
    res->big_int_unsigned_add(b);
    res->big_int_unsigned_add(*this);
    return 0;

}

int bi::big_int::big_int_unsigned_sub(const bi::big_int &b, bi::big_int *res) {

    int max, min;
    max = _top;
    min = b._top;

    int diff = max - min;
    if(diff < 0) {
        throw std::length_error("First param should be larger");
    }

    (void) max;
    res->big_int_clear();
    _sub_base_type(b._data, min, res);
    return 0;

}

int bi::big_int::big_int_clear() {

    memset(_data, 0, static_cast<size_t>(_total_data) * sizeof(BI_BASE_TYPE));
    _top            = 0;
    _neg            = false;
    return 0;
}

std::string     bi::big_int::big_int_to_string(bi::bi_base base) {

    // TODO: Need to return string instead of printing it

    std::string op_string;

    for(int i = 0; i < _top; ++i) {
        if(base == bi::bi_base::BI_DEC) {
            _BI_LOG(1, "d %010u", _data[i]);
        }
        else if(base == bi::bi_base::BI_HEX){ 
            _BI_LOG(1, "0x %08X", _data[i]);
        }
    }

    printf("\n");

    return op_string;

}

int bi::big_int::_sub_base_type(BI_BASE_TYPE *data_ptr, int min, bi::big_int *res_ptr) {

    BI_BASE_TYPE borrow = 0;
    BI_DOUBLE_BASE_TYPE diff, temp1;
    for(int i = 0; i < min; ++i) {
        if(compare_bi_base_type(&_data[i], &data_ptr[i])) {
            diff = _data[i] - data_ptr[i] - borrow;
            borrow = 0;
        } else {
            temp1 = _data[i] + 0xFFFFFFFF - borrow;
            diff = temp1 - data_ptr[i];
            borrow = 1;
        }
        res_ptr->_data[(res_ptr->_top)++] = static_cast<BI_BASE_TYPE>(diff);
    }
    return 0;
}

namespace {

    static int compare_bi_base_type(const BI_BASE_TYPE *a, const BI_BASE_TYPE *b) {

        if(a > b)
            return 1;
        else
            return 0;

    }

}