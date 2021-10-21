/** 
 *  @file   big_int_priv_defs.cc
 *  @brief  Big int private member definitions
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include <algorithm>
#include <stdexcept>

#include "big_int.hpp"
#include "big_int_lib_log.hpp"
#include "big_int_inline_defs.hpp"

void bi::big_int::_big_int_swap(bi::big_int &src) {

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

BI_BASE_TYPE bi::big_int::_big_int_sub_base_type(BI_BASE_TYPE *data_ptr, int min, bi::big_int *res_ptr) const {

    BI_BASE_TYPE borrow = 0;
    BI_DOUBLE_BASE_TYPE diff, temp1;
    if (res_ptr->_total_data <= min) {
        res_ptr->_big_int_expand(BI_DEFAULT_EXPAND_COUNT + min);
    }
    for(int i = 0; i < min; ++i) {
        if(compare_bi_base_type(_data[i], data_ptr[i])) {
            diff = _data[i] - data_ptr[i] - borrow;
            borrow = 0;
        } else {
            temp1 = static_cast<BI_DOUBLE_BASE_TYPE>(_data[i]) + BI_BASE_TYPE_MAX + 1 - borrow;
            diff = temp1 - data_ptr[i];
            borrow = 1;
        }
        res_ptr->_data[(res_ptr->_top)++] = static_cast<BI_BASE_TYPE>(diff);
    }
    return borrow;
}

int bi::big_int::_big_int_compare_bi_base_type_n_top(const bi::big_int &other) const {

    if (_top == other._top) {
        int i = _top - 1;
        for(; i >= 0; i--) {
            if (_data[i] == other._data[i]) {
                continue;
            } else if (_data[i] > other._data[i]) {
                return 1;
            } else {
                return -1;
            }
        }
        return 0;
    } else if (_top > other._top) {
        return 1;
    } else {
        return -1;
    }

}

int bi::big_int::_big_int_unsigned_multiply_bi_base_type(BI_BASE_TYPE b, bi::big_int *res_ptr) const {

    BI_DOUBLE_BASE_TYPE interim_res;
    BI_BASE_TYPE        carry = 0;

    res_ptr->big_int_clear();

    if (_top >= res_ptr->_total_data) {
        res_ptr->_big_int_expand(BI_DEFAULT_EXPAND_COUNT + _top);
    }

    for(int i = 0; i < _top; ++i) {
        interim_res = static_cast<BI_DOUBLE_BASE_TYPE>(_data[i]) * b + carry;
        res_ptr->_data[(res_ptr->_top)++] = interim_res & BI_BASE_TYPE_MAX;
        carry = static_cast<BI_BASE_TYPE>(interim_res >> BI_BASE_TYPE_TOTAL_BITS);
    }

    if (carry) {
        if (res_ptr->_top >= res_ptr->_total_data) {
            res_ptr->_big_int_expand(BI_DEFAULT_EXPAND_COUNT);
        }
        res_ptr->_data[(res_ptr->_top)++] = carry;
    }

    return 0;

}

int bi::big_int::_big_int_left_shift_below_32bits(int bits) {

    if (bits > 32) {
        return -1;
    }

    BI_DOUBLE_BASE_TYPE interim_res;
    BI_BASE_TYPE        carry = 0;

    if (_top >= _total_data) {
        _big_int_expand(BI_DEFAULT_EXPAND_COUNT + _top);
    }

    for (int i = 0; i < _top; ++i) {
        interim_res = (static_cast<BI_DOUBLE_BASE_TYPE>(_data[i]) << bits) + carry;
        carry = static_cast<BI_BASE_TYPE>(interim_res >> BI_BASE_TYPE_TOTAL_BITS);
        _data[i] = static_cast<BI_BASE_TYPE>(interim_res & BI_BASE_TYPE_MAX);
    }

    if (carry) {
        _data[_top++] = carry;
    }

    return 0;

}

int bi::big_int::_big_int_right_shift_below_32bits(int bits) {

    if (bits > 32) {
        return -1;
    }

    BI_DOUBLE_BASE_TYPE interim_res_1, interim_res_2;
    BI_BASE_TYPE        carry = 0;

    for (int i = _top - 1; i >= 0; --i) {
        interim_res_1 = static_cast<BI_DOUBLE_BASE_TYPE>(_data[i]) << BI_BASE_TYPE_TOTAL_BITS;
        interim_res_2 = (interim_res_1 >> bits);
        _data[i] = static_cast<BI_BASE_TYPE>((interim_res_2 & BI_DOUBLE_BASE_TYPE_FIRST_HALF_MASK) >> BI_BASE_TYPE_TOTAL_BITS) + carry;
        carry = interim_res_2 & BI_BASE_TYPE_MAX;
    }

    /* No need to save carry as its a right shift and those bits are discarded. */

    return _big_int_remove_preceding_zeroes();

}

int bi::big_int::_big_int_remove_preceding_zeroes() {

    int i = _top - 1;
    for(; i > 0; i--) {
        if(_data[i] == 0) {
            _top--;
        } else {
            return 0;
        }
    }

    if(_data[0] == 0) {
        /* The big int is zero, set the sign to positve just in case. */
        _neg = false;
    }

    return 0;

}

int bi::big_int::_big_int_get_num_of_hex_chars() const {

    int ret_val = 0;
    if (_top > 1) {
        ret_val += (_top - 1) * 8;
    }

    if (_top >= 1) {
        BI_BASE_TYPE temp_val = _data[_top - 1];
        
        do {
            ret_val += 1;
        } while (temp_val >>= 4);
    }

    return ret_val;

}

int bi::big_int::_big_int_divide_once(const big_int &divisor, BI_BASE_TYPE &op_quotient, big_int &op_remainder) {

    if (divisor.big_int_is_zero()) {
        // throw std::length_error("Division by zero undefined");
        return -1;
    }

    if (_big_int_get_num_of_hex_chars() - divisor._big_int_get_num_of_hex_chars() > 1) {
        /* Return error as this api will only divide once. */
        return -1;
    }

    if (big_int_is_zero()) {
        /* Set remainder and quotient as zero if dividend is zero. */
        op_remainder.big_int_set_zero();
        op_quotient = 0;
        return 0;
    }

    int comp_res = big_int_unsigned_compare(divisor);
    switch (comp_res) {
    case -1:
        /* Divisor is greater than dividend, set quotient as zero 
        and remainder as dividend */
        op_remainder = *this;
        op_quotient = 0;
        return 0;
    case 0:
        /* Both dividend and divisor are same, so set quotient as 1 and remainder as zero. */
        op_quotient = 1;
        op_remainder.big_int_set_zero();
        return 0;
    }

    big_int temp_val, temp_val_2;

    /* Start from 2 as the cases 0 & 1 are covered already in the above lines. */
    BI_BASE_TYPE i = 2;
    for (; i <= 0x10; ++i) {
        divisor.big_int_unsigned_multiply_base_type(i, &temp_val);
        comp_res = big_int_unsigned_compare(temp_val);
        switch (comp_res) {
        case -1:
            op_quotient = i - 1;
            divisor.big_int_unsigned_multiply_base_type(i - 1, &temp_val_2);
            big_int_unsigned_sub(temp_val_2, &op_remainder);
            return 0;
        case 0:
            op_quotient = i;
            op_remainder.big_int_set_zero();
            return 0;
        }
    }

    /* Function shouldn't reach here. ERROR. */
    return -1;

}

int bi::big_int::_big_int_push_back_hex_chars(const BI_BASE_TYPE &hex_char) {

    if (hex_char > 0xF) {
        return -1;
    }

    if (hex_char == 0 && big_int_is_zero() == true) {
        /* MSB is zero, do nothing */
        return 0;
    }

    int ret_val;
    ret_val = big_int_left_shift(4);
    _data[0] += hex_char;
    return ret_val;

}

int bi::big_int::_big_int_get_hex_char_from_lsb(int hex_indx_from_lsb, BI_BASE_TYPE &hex_char) const {

    hex_char = 0;
    if (hex_indx_from_lsb < 0) {
        return -1;
    }

    /* hex_indx_from_lsb starts from 0. */
    int data_indx = hex_indx_from_lsb / (BI_BASE_TYPE_TOTAL_BITS / 4);
    int next_idx = hex_indx_from_lsb % (BI_BASE_TYPE_TOTAL_BITS / 4);

    if (data_indx >= _top) {
        return -1;
    }

    BI_BASE_TYPE temp_data = _data[data_indx];
    hex_char = (temp_data >> (next_idx * 4)) & 0xF;
    return 0;

}

int bi::big_int::_big_int_fast_modular_exponentiation(const bi::big_int &exponent, const bi::big_int &modulus, bi::big_int &result) {

    int ret_val = 0;

    if (exponent.big_int_is_zero() == true && modulus.big_int_is_negetive() == true) {
        big_int bi_1;
        bi_1.big_int_from_base_type(1, false);
        ret_val += modulus.big_int_unsigned_sub(bi_1, &result);
        ret_val += result.big_int_set_negetive(true);
        return ret_val;
    }

    
    ret_val += result.big_int_from_base_type(1, false);
    big_int bi_2;
    ret_val += bi_2.big_int_from_base_type(2, false);
    
    big_int temp_base(*this), temp_exponent(exponent), temp_exponent_2, temp_result, temp_result_2;
    BI_BASE_TYPE temp_exponent_rem;
    while (temp_exponent.big_int_is_zero() == false) {
        ret_val += temp_exponent._big_int_fast_divide_by_two(temp_exponent_rem);
        if (temp_exponent_rem != 0) {
            ret_val += result.big_int_multiply(temp_base, &temp_result);
            ret_val += temp_result.big_int_modulus(modulus, temp_result_2);
            result = temp_result_2;
        }
        ret_val += temp_base.big_int_multiply(temp_base, &temp_result);
        ret_val += temp_result.big_int_modulus(modulus, temp_result_2);
        temp_base = temp_result_2;
    }
    return ret_val;

}

int bi::big_int::_big_int_fast_divide_by_two(BI_BASE_TYPE &remainder) {

    BI_DOUBLE_BASE_TYPE interim_res_1, interim_res_2;
    BI_BASE_TYPE        carry = 0;

    for (int i = _top - 1; i >= 0; --i) {
        interim_res_1 = static_cast<BI_DOUBLE_BASE_TYPE>(_data[i]) << BI_BASE_TYPE_TOTAL_BITS;
        interim_res_2 = (interim_res_1 >> 1);
        _data[i] = static_cast<BI_BASE_TYPE>((interim_res_2 & BI_DOUBLE_BASE_TYPE_FIRST_HALF_MASK) >> BI_BASE_TYPE_TOTAL_BITS) + carry;
        carry = interim_res_2 & BI_BASE_TYPE_MAX;
    }
    remainder = carry;
    return _big_int_remove_preceding_zeroes();

}