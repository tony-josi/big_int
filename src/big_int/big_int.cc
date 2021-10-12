/** 
 *  @file   big_int.cc
 *  @brief  Main source file for the big int library
 *
 *  This file contains the source code and the DS used in the big int library
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include <stdexcept>
#include <algorithm>
#include <string.h>
#include <memory>
#include <cstdio>

#include "big_int.hpp"
#include "big_int_lib_log.hpp"
#include "big_int_inline_defs.hpp"

int bi::big_int::big_int_from_string(const std::string &str_num) {

    size_t str_size = str_num.length(), num_decor_cnt = 0;
    size_t is_neg = 0;
    if (str_size > 0 && str_num[0] == '-') {
        is_neg = 1;
        num_decor_cnt += 1;
    }
    if((str_size > (1 + is_neg)) && str_num[is_neg] == '0' && \
    (str_num[is_neg + 1] == 'x' || str_num[is_neg + 1] == 'X')) {
        num_decor_cnt += 2;
    }

    str_size -= num_decor_cnt;

    /* Clear any previous data. */
    big_int_clear();

    size_t extr_space_reqd = ((str_size % BI_HEX_STR_TO_DATA_SIZE == 0) ? \
    0 : (BI_HEX_STR_TO_DATA_SIZE - (str_size % BI_HEX_STR_TO_DATA_SIZE)));
    
    size_t base_t_aligned_size = str_size + extr_space_reqd;
    std::unique_ptr<char []> temp_str(new char[base_t_aligned_size]);
    memset(temp_str.get(), '0', extr_space_reqd);
    memcpy(temp_str.get() + extr_space_reqd, str_num.c_str() + num_decor_cnt, str_size);

    int str_cur_indx = static_cast<int>(base_t_aligned_size - BI_HEX_STR_TO_DATA_SIZE);

    for(; str_cur_indx >= 0; str_cur_indx -= static_cast<int>(BI_HEX_STR_TO_DATA_SIZE)) {
        if(sscanf(&(temp_str.get()[str_cur_indx]), BI_SSCANF_FORMAT_HEX, &_data[_top++]) == EOF) {
            big_int_clear();
            return -1;
        }
        if(_top == _total_data) {
            _big_int_expand(BI_DEFAULT_EXPAND_COUNT);
        }
    }

    if(big_int_is_zero() == true && is_neg) {
        return -1;
    }
    _neg = static_cast<bool>(is_neg);

    /* Remove extra zeroes in the MSB if the i/p string had them, except the last zero (to denote zero big integer).*/
    _big_int_remove_preceding_zeroes();

    return 0;

}

int bi::big_int::big_int_from_base_type(const BI_BASE_TYPE &bt_val, const bool is_neg) {

    big_int_clear();
    _data[_top++] = bt_val;
    _neg = is_neg;
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
        sum = static_cast<BI_DOUBLE_BASE_TYPE>(b._data[i]) + _data[i] + carry;
        carry = static_cast<BI_BASE_TYPE>((sum) >> BI_BASE_TYPE_TOTAL_BITS);
        _data[i] = sum & BI_BASE_TYPE_MAX;
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
            sum = static_cast<BI_DOUBLE_BASE_TYPE>(_data[i]) + carry;
        } else {
            sum = static_cast<BI_DOUBLE_BASE_TYPE>(b._data[i]) + carry;
        }
        carry = static_cast<BI_BASE_TYPE>((sum) >> BI_BASE_TYPE_TOTAL_BITS);
        _data[i] = sum & BI_BASE_TYPE_MAX;
    }
    _top += top_cntr;
    
    if (carry) {
        if(i >= _total_data) {
            _big_int_expand(BI_DEFAULT_EXPAND_COUNT);
        }
        _data[_top++] = carry;
    }

    return 0;

}

int bi::big_int::big_int_unsigned_add(const bi::big_int &b, bi::big_int *res) {

    res->big_int_clear();
    res->big_int_unsigned_add(b);
    res->big_int_unsigned_add(*this);
    return 0;

}

int bi::big_int::big_int_signed_add(const bi::big_int &b) {

    bi::big_int temp;
    big_int_signed_add(b, &temp);
    _big_int_swap(temp);
    return 0;

}

int bi::big_int::big_int_signed_add(const bi::big_int &b, bi::big_int *res) {

    res->big_int_clear();
    /* If the operands are of same sign. */
    if (_neg == b._neg) {

        big_int_unsigned_add(b, res);
        res->_neg = _neg;

    }
    /* If operands are of different sign. */
    else {

        /* Convert to same type. */
        _neg = !_neg;
        int comp_stat = big_int_compare(b);
        if (comp_stat == 1) {
            if (_neg) {
                b.big_int_unsigned_sub(*this, res);
                res->_neg = b._neg;
            } else {
                big_int_unsigned_sub(b, res);
                res->_neg = !_neg;
            }
        } else if (comp_stat == 0) {
            res->big_int_set_zero();
        } else {
            if (_neg) {
                big_int_unsigned_sub(b, res);
                res->_neg = !_neg;
            } else {
                b.big_int_unsigned_sub(*this, res);
                res->_neg = b._neg;
            }
        }

        /* Set back to previous type. */
        _neg = !_neg;

    }

    /* Remove any preceding zeroes if any. */
    res->_big_int_remove_preceding_zeroes();

    return 0;

}

int bi::big_int::big_int_left_shift_word(int shift_words) {

    if (shift_words < 0) {
        return -1;
    }

    if (shift_words == 0) {
        return 0;
    }

    if (_top + shift_words >= _total_data) {
        _big_int_expand(BI_DEFAULT_EXPAND_COUNT + shift_words);
    }
    
    for (int i = _top - 1; i >= 0; --i) {
        _data[i + shift_words] = _data[i];
    }
    _top += shift_words;

    for (int i = 0; i < shift_words; ++i) {
        _data[i] = 0;
    }
    return 0;

}

int bi::big_int::big_int_signed_sub(const bi::big_int &b) {

    int ret_val;
    bi::big_int temp_val;
    ret_val = big_int_signed_sub(b, &temp_val);
    _big_int_swap(temp_val);
    return ret_val;

}

int bi::big_int::big_int_signed_sub(const bi::big_int &b, bi::big_int *res) {

    int comp_stat = big_int_compare(b);
    if (comp_stat == 0) {
        return res->big_int_set_zero();
    } else {

        // TODO: avoid expensive (might be) copy here
        bi::big_int temp_sub(b);
        temp_sub._neg = !temp_sub._neg;
        return big_int_signed_add(temp_sub, res);
    }

}

int bi::big_int::big_int_set_zero() {

    big_int_clear();
    if (_total_data > 0) {
        _top = 1;
    } else {
        return 1;
    }
    return 0;

}

int bi::big_int::big_int_unsigned_sub(const bi::big_int &b, bi::big_int *res) const {

    int max, min;
    max = _top;
    min = b._top;

    int diff = max - min;
    if(diff < 0) {
        throw std::length_error("First param should be larger");
    }

    res->big_int_clear();
    BI_BASE_TYPE borrow = _big_int_sub_base_type(b._data, min, res);

    for(int i = min; i < max; i++) {
        if(i >= res->_total_data) {
            res->_big_int_expand(BI_DEFAULT_EXPAND_COUNT);
        }
        if(compare_bi_base_type(_data[i], borrow)) {
            res->_data[(res->_top)++] = _data[i] - borrow;
            borrow = 0;
        } else {
            res->_data[(res->_top)++] = \
            static_cast<BI_BASE_TYPE>((static_cast<BI_DOUBLE_BASE_TYPE>(BI_BASE_TYPE_MAX) + 1 - borrow));
            borrow = 1;
        }
    }

    res->_big_int_remove_preceding_zeroes();

    return 0;

}

int bi::big_int::big_int_unsigned_sub(const bi::big_int &b) {

    bi::big_int temp;
    big_int_unsigned_sub(b, &temp);
    temp._neg = this->_neg;
    _big_int_swap(temp);
    return 0;

}

int bi::big_int::big_int_multiply(const bi::big_int &b, bi::big_int *res) {

    bi::big_int temp_bi;

    res->big_int_set_zero();

    if(big_int_is_zero() || b.big_int_is_zero()) {
        /* If any/both of the opreands is zero set result as zero and exit */
        return 0;
    }

    res->_neg = _neg ^ b._neg;
    
    for (int i = 0; i < b._top; ++i) {
        temp_bi.big_int_clear();
        _big_int_unsigned_multiply_bi_base_type(b._data[i], &temp_bi);
        temp_bi.big_int_left_shift_word(i);
        res->big_int_unsigned_add(temp_bi);
    }
    return 0;

}

int bi::big_int::big_int_unsigned_multiply_base_type(const BI_BASE_TYPE &b, bi::big_int *res) const {

    return _big_int_unsigned_multiply_bi_base_type(b, res);

}

int bi::big_int::big_int_clear() {

    memset(_data, 0, static_cast<size_t>(_total_data) * sizeof(BI_BASE_TYPE));
    _top            = 0;
    _neg            = false;
    return 0;
}

std::string     bi::big_int::big_int_to_string(bi::bi_base base) {

    size_t chars_per_data;

    if (_top <= 0) {
        throw std::length_error("Invalid number: zero length");
    }

    if(base == bi::bi_base::BI_DEC) {
        chars_per_data = BI_SPRINF_FORMAT_DEC_CHARS;
    } else if(base == bi::bi_base::BI_HEX){ 
        chars_per_data = BI_SPRINF_FORMAT_HEX_CHARS;
    } else {
        chars_per_data = 0;
    }

    size_t is_neg = 0;
    if (big_int_is_negetive()) {
        is_neg = 1;
    }

    std::unique_ptr<char []> char_temp_buff(new char[static_cast<size_t>(_top) * chars_per_data + 1 + is_neg]);
    memset(char_temp_buff.get(), '\0', static_cast<size_t>(_top) * chars_per_data + 1 + is_neg);
    if (is_neg) {
        char_temp_buff.get()[0] = '-';
    }

    for(int i = _top - 1; i >= 0; --i) {
        
        if(base == bi::bi_base::BI_DEC) {
            sprintf(char_temp_buff.get() + is_neg + ((static_cast<size_t>(_top) - 1) - static_cast<size_t>(i)) * \
            chars_per_data, BI_SPRINF_FORMAT_DEC, _data[i]);
            _BI_LOG(3, BI_SPRINF_FORMAT_DEC_LOG, _data[i]);
        }
        else if(base == bi::bi_base::BI_HEX){ 
            sprintf(char_temp_buff.get() + is_neg + ((static_cast<size_t>(_top) - 1) - static_cast<size_t>(i)) * \
            chars_per_data, BI_SPRINF_FORMAT_HEX, _data[i]);
            _BI_LOG(3, BI_SPRINF_FORMAT_HEX_LOG, _data[i]);
        }
        
    }

    std::string op_string(char_temp_buff.get());
    return op_string;

}

int bi::big_int::big_int_set_negetive(bool set_unset) {

    if (big_int_is_zero()) {
        return -1;
    }
    _neg = set_unset;
    return 0;

}

bool bi::big_int::big_int_is_zero() const {

    if (_top > 1) {
        return false;
    } else if (_top == 1) {
        if (_data[0] == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

}


bool bi::big_int::big_int_is_negetive() const {

    return _neg;

}

int bi::big_int::big_int_unsigned_compare(const bi::big_int &other) const {

    return _big_int_compare_bi_base_type_n_top(other);

}

int bi::big_int::big_int_compare(const bi::big_int &other) const {

    if (_neg == other._neg) {
        if (_neg == 1) {
            return -1 * _big_int_compare_bi_base_type_n_top(other);
        } else {
            return _big_int_compare_bi_base_type_n_top(other);
        }
    } else {
        if (_neg == 1) {
            return -1;
        } else {
            return 1;
        }
    }
}

int bi::big_int::big_int_left_shift(int bits) {

    int ret_val = 0;
    int word_shifts = bits / BI_BASE_TYPE_TOTAL_BITS;
    int bit_shifts = bits % BI_BASE_TYPE_TOTAL_BITS;
    if (word_shifts > 0) {
        ret_val = big_int_left_shift_word(word_shifts);
    }
    if (bit_shifts > 0) {
        ret_val += _big_int_left_shift_below_32bits(bit_shifts);
    }
    return ret_val;

}

int bi::big_int::big_int_left_shift(int bits, bi::big_int *res) {

    int ret_val;
    big_int temp_val(*this);
    ret_val = temp_val.big_int_left_shift(bits);
    temp_val._big_int_swap(*res);
    return ret_val;

}

int bi::big_int::big_int_left_shift_word(int shift_words, bi::big_int *res) {

    int ret_val;
    big_int temp_val(*this);
    ret_val = temp_val.big_int_left_shift_word(shift_words);
    temp_val._big_int_swap(*res);
    return ret_val;

}

int bi::big_int::big_int_right_shift_word(int shift_words) {

    if (shift_words >= _top) {
        return big_int_set_zero();
    }

    int i = 0;
    for (; i < _top - shift_words; ++i) {
        _data[i] = _data[i + shift_words];
    }
    for (int j = 0; j < shift_words; ++j) {
        _data[i + j] = 0;
    }

    _top -= shift_words;

    return 0;

}

int bi::big_int::big_int_right_shift_word(int shift_words, bi::big_int *res) {

    int ret_val;
    big_int temp_val(*this);
    ret_val = temp_val.big_int_right_shift_word(shift_words);
    temp_val._big_int_swap(*res);
    return ret_val;

}

int bi::big_int::big_int_right_shift(int bits) {

    int ret_val = 0;
    int word_shifts = bits / BI_BASE_TYPE_TOTAL_BITS;
    int bit_shifts = bits % BI_BASE_TYPE_TOTAL_BITS;
    if (word_shifts > 0) {
        ret_val = big_int_right_shift_word(word_shifts);
    }
    if (bit_shifts > 0) {
        ret_val += _big_int_right_shift_below_32bits(bit_shifts);
    }
    return ret_val;

}

int bi::big_int::big_int_right_shift(int bits, bi::big_int *res) {

    int ret_val;
    big_int temp_val(*this);
    ret_val = temp_val.big_int_right_shift(bits);
    temp_val._big_int_swap(*res);
    return ret_val;

}

int bi::big_int::big_int_get_num_of_hex_chars() {

    return _big_int_get_num_of_hex_chars();

}

int bi::big_int::big_int_push_back_hex_chars(const BI_BASE_TYPE &hex_chars) {

    return _big_int_push_back_hex_chars(hex_chars);

}

int bi::big_int::big_int_divide_once(const bi::big_int &divisor, BI_BASE_TYPE &op_quotient, bi::big_int &op_remainder) {

    return _big_int_divide_once(divisor, op_quotient, op_remainder);

}

int bi::big_int::big_int_div(const bi::big_int &divisor, bi::big_int &op_quotient, bi::big_int &op_remainder) {

    if (divisor.big_int_is_zero()) {
        // throw std::length_error("Division by zero undefined");
        return -1;
    }

    bool result_sign = big_int_is_negetive() ^ divisor.big_int_is_negetive();

    if (big_int_is_zero()) {
        /* Set remainder and quotient as zero if dividend is zero. */
        op_remainder.big_int_set_zero();
        op_quotient.big_int_set_zero();
        return 0;
    }

    int comp_res = big_int_unsigned_compare(divisor);
    switch (comp_res) {
    case -1:
        /* Divisor is greater than dividend, set quotient as zero 
        and remainder as dividend */
        op_remainder = *this;
        /* Remainder takes the sign of dividend. */
        op_remainder.big_int_set_negetive(_neg);
        op_quotient.big_int_set_zero();
        return 0;
    case 0:
        /* Both dividend and divisor are same, so set quotient as 1 and remainder as zero. */
        op_quotient.big_int_from_base_type(static_cast<BI_BASE_TYPE>(1), result_sign);
        op_remainder.big_int_set_zero();
        return 0;
    case 1:

        /* Clear quotient and remainder big ints. */
        op_quotient.big_int_set_zero();

        BI_BASE_TYPE temp_div_once_quotient, temp_new_hex_rem_lsb = 0;
        bi::big_int temp_div_once_dividend, temp_div_once_remainder; 
        int divisor_length = divisor._big_int_get_num_of_hex_chars();
        int dividend_length = _big_int_get_num_of_hex_chars();
        int ret_code = big_int_right_shift((dividend_length - divisor_length) * 4, &temp_div_once_dividend);
        int divide_cntr = 0;
        
        do {
        
            /* Divide once. */
            temp_div_once_quotient = 0;
            temp_div_once_remainder.big_int_clear();
            ret_code += temp_div_once_dividend._big_int_divide_once(divisor, temp_div_once_quotient, temp_div_once_remainder);
            ret_code += op_quotient._big_int_push_back_hex_chars(temp_div_once_quotient);

            if ((dividend_length - divisor_length - divide_cntr - 1) >= 0) {
                ret_code += _big_int_get_hex_char_from_lsb(dividend_length - divisor_length - divide_cntr - 1, temp_new_hex_rem_lsb);
            } 
            
            temp_div_once_dividend = temp_div_once_remainder;
            ret_code += temp_div_once_dividend.big_int_push_back_hex_chars(temp_new_hex_rem_lsb);
            ++divide_cntr;
        
        } while ((dividend_length - divisor_length + 1 - divide_cntr) > 0 && ret_code == 0);
        
        op_remainder = temp_div_once_remainder;
        op_quotient.big_int_set_negetive(result_sign);

        /* Remainder takes the sign of dividend. */
        op_remainder.big_int_set_negetive(_neg);

        return ret_code;

    }

    /* Should't reach here. */
    return -1;

}

int bi::big_int::big_int_power_base_type(const BI_BASE_TYPE &exponent, big_int &result) {

    int ret_val = 0;

    if (big_int_is_zero()) {
        if (exponent == 0) {
            /* pow(0, 0) = 1 */
            return result.big_int_from_base_type(1, false);
        } else {
            /* pow(0, anything except 0) = 0 */
            return result.big_int_set_zero();
        }
    }
    
    ret_val += result.big_int_from_base_type(1, false);

    big_int temp_val;
    for (BI_BASE_TYPE i = 0; i < exponent; ++i) {
        ret_val += big_int_multiply(result, &temp_val);
        result = temp_val;
    }

    return ret_val;

}

int bi::big_int::big_int_modulus(const big_int &modulus, big_int &result) {

    big_int temp_quo, temp_rem;
    int ret_val = 0;

    ret_val += big_int_div(modulus, temp_quo, temp_rem);
    if (modulus.big_int_is_negetive() == false) {
        if (temp_rem.big_int_is_negetive() == true) {
            ret_val += modulus.big_int_unsigned_sub(temp_rem, &result);
        } else {
            result = temp_rem;
        }
    } else {
        if ((temp_rem.big_int_is_negetive() == false) && (temp_rem.big_int_is_zero() == false)) {
            ret_val += modulus.big_int_unsigned_sub(temp_rem, &result);   
        } else {
            result = temp_rem;
        }
        ret_val += result.big_int_set_negetive(true);
    }
    return ret_val;

}


/*

    Fast modular exponentiation algorithm
    -------------------------------------
    
    [refer](https://stackoverflow.com/questions/40578553/fast-modular-exponentiation-help-me-find-the-mistake)
    [refer](http://homepages.math.uic.edu/~leon/cs-mcs401-s08/handouts/fastexp.pdf)

    Algorithm - python:
    -------------------

        def pow_h(base, power, modulus):
            a = 1
            while power:
                power, d = power // 2, power % 2
                if d:
                    a = a * base % modulus
                base = base * base % modulus
            return a

    Example:    8 ^ 5 mod 7

    Result is initialized to 1
    prev_base = 7, initial base during first iteration
    n_base => next base

    +----------------------+----------------------+----------------------+----------------------+
    | Itertion             | Exponent bit         | Calculation          | Result               |
    +----------------------+----------------------+----------------------+----------------------+
    | 1                    | 1                    | prev_base = 7        | 1 * 8 mod 7 = 1      | 
    |                      |                      | n_base = 8 mod 7 = 1 |                      |
    +----------------------+----------------------+----------------------+----------------------+
    | 2                    | 0                    | n_base = 8 ^ 2 mod 7 | No result calc. if   |
    |                      |                      | = 1 * 1 mod 7 = 1    | exponent bit is zero |
    +----------------------+----------------------+----------------------+----------------------+
    | 3                    | 1                    | n_base = 8 ^ 4 mod 7 | 1 * 1 mod 7 = 1      |
    |                      |                      | = 8 ^ 2 * 8 ^ 2 mod 7|                      |
    |                      |                      | = 1 * 1 mod 7 = 1    |                      |
    +----------------------+----------------------+----------------------+----------------------+

*/
int bi::big_int::big_int_fast_modular_exponentiation(const big_int &exponent, const big_int &modulus, big_int &result) {

    // TODO: Test if base could be negetive.
    if (exponent.big_int_is_negetive() || big_int_is_negetive()) {
        throw std::range_error("Doesnt support negetive exponents/base for big_int_modular_exponentiation");
    }

    big_int bi_1;
    bi_1.big_int_from_base_type(1, false);
    int comp_res = modulus.big_int_compare(bi_1);
    if (comp_res < 0) {
        // TODO: check if mod can be -ve.
        throw std::range_error("Doesnt support negetive or zero modulus");
    } else if (comp_res == 0) {
        /* Set result as 0 if modulus is 1. */
        return result.big_int_set_zero();
    }

    if (exponent.big_int_is_zero() == true) {
        /* Set result as 1 if exponent is zero. */
        return result.big_int_from_base_type(1, false);
    }

    if (big_int_is_zero() == true) {
        return result.big_int_set_zero();
    }

    result.big_int_from_base_type(1, false);
    big_int bi_2;
    bi_2.big_int_from_base_type(2, false);

    int ret_val = 0;
    big_int temp_exponent(exponent), temp_exponent_2, temp_exponent_quo, temp_exponent_rem, temp_result, temp_result_2;
    while (temp_exponent.big_int_is_zero() == false) {
        ret_val += temp_exponent.big_int_div(bi_2, temp_exponent_quo, temp_exponent_rem);
        temp_exponent = temp_exponent_quo;
        if (temp_exponent_rem.big_int_is_zero() == false) {
            ret_val += result.big_int_multiply(*this, &temp_result);
            ret_val += temp_result.big_int_modulus(modulus, temp_result_2);
            result = temp_result_2;
        }
        ret_val += big_int_multiply(*this, &temp_result);
        ret_val += temp_result.big_int_modulus(modulus, temp_result_2);
        *this = temp_result_2;
    }
    return ret_val;
}


/*

    GCD - Euclidean algorithm
    -------------------------

    [refer](https://en.wikipedia.org/wiki/Euclidean_algorithm)

    For illustration, the Euclidean algorithm can be used to find the greatest common divisor of a = 1071 and b = 462. 
    To begin, multiples of 462 are subtracted from 1071 until the remainder is less than 462. Two such multiples can be subtracted (q0 = 2), 
    leaving a remainder of 147:

        1071 = 2 × 462 + 147.
    
    Then multiples of 147 are subtracted from 462 until the remainder is less than 147. Three multiples can be subtracted (q1 = 3), leaving a remainder of 21:

        462 = 3 × 147 + 21.
    
    Then multiples of 21 are subtracted from 147 until the remainder is less than 21. Seven multiples can be subtracted (q2 = 7), leaving no remainder:

        147 = 7 × 21 + 0.
    
    Since the last remainder is zero, the algorithm ends with 21 as the greatest common divisor of 1071 and 462. 

*/

int bi::big_int::big_int_gcd_euclidean_algorithm(const big_int &b, big_int &op_gcd) {

    if (((*this).big_int_is_zero() & b.big_int_is_zero()) == true) {
        /* If both numbers are zero gcd is zero. */
        return op_gcd.big_int_set_zero();
    } else if ((*this).big_int_is_zero()) {
        /* If one of the number is zero and other is non zero then gcd is the non
        zero number. */
        op_gcd = b;
        return  op_gcd.big_int_set_negetive(false);
    } else if (b.big_int_is_zero()) {
        /* If one of the number is zero and other is non zero then gcd is the non
        zero number. */
        op_gcd = (*this);
        return op_gcd.big_int_set_negetive(false);    
    }

    /* Temp working variables. */
    big_int temp_greater, temp_lower, temp_quo, temp_rem, prev_rem;

    /* Compare and assign greater and lower big int temp variables. */
    int ret_code = 0, comp_stat = (*this).big_int_unsigned_compare(b);
    if (comp_stat == 0) {
        /* If both numbers are equal then gcd is equal to the +ve number. */
        op_gcd = (*this);
        return op_gcd.big_int_set_negetive(false);
    } else if (comp_stat == 1) {
        temp_greater = (*this);
        temp_lower = b;
    } else {
        temp_greater = b;
        temp_lower = (*this);
    }

    /* Set the numbers as positve as the gcd is +ve. */
    temp_greater.big_int_set_negetive(false); temp_lower.big_int_set_negetive(false);

    /* Initialse the temp_rem and thus prev_rem with the lower number so that,
    the gcd will be the lower number when both numbers are multiples. */
    temp_rem = temp_lower;
    do {
        /* GCD Euclidean algorithm (refer func. docs.) */
        prev_rem = temp_rem;
        ret_code += temp_greater.big_int_div(temp_lower, temp_quo, temp_rem);
        temp_greater = temp_lower;
        temp_lower = temp_rem;
    } while(temp_rem.big_int_is_zero() == false);

    /* Assign previous remainder as the gcd. */
    op_gcd = prev_rem;
    return ret_code;

}

int bi::big_int::big_int_modular_inverse_extended_euclidean_algorithm(const big_int &modulus, big_int &inverse) {

    big_int bi_1;
    bi_1.big_int_from_base_type(1, false);

    int ret_code = 0;
    /* Extended euclidean algorithm (EEA) working variables */
    big_int pk_0, pk_1, pk_temp_1, pk_temp_2;
    /* Init the variables to 0 and 1. */
    pk_1.big_int_from_base_type(1, false);

    int step_cntr = 0;
    /* Temp working variables. */
    big_int temp_greater, temp_lower, temp_quo, temp_rem, prev_rem, prev_quo[2];

    /* Compare and assign greater and lower big int temp variables. */
    int comp_stat = (*this).big_int_unsigned_compare(modulus);
    if (comp_stat == 0) {
        /* If both numbers are equal then invrese is equal to the +ve number. Only in the case of 1 */
        /* TODO: verify above line. */
        inverse = (*this);
        return inverse.big_int_set_negetive(false);
    } else if (comp_stat == 1) {
        temp_greater = (*this);
        temp_lower = modulus;
    } else {
        temp_greater = modulus;
        temp_lower = (*this);
    }

    temp_rem = temp_lower;
    do {
        ++step_cntr;
        prev_rem = temp_rem;
        prev_quo[0] = prev_quo[1];
        prev_quo[1] = temp_quo;
        ret_code += temp_greater.big_int_div(temp_lower, temp_quo, temp_rem);
        temp_greater = temp_lower;
        temp_lower = temp_rem;
        if (step_cntr > 2) {
            ret_code += pk_1.big_int_multiply(prev_quo[0], &pk_temp_1);
            ret_code += pk_0.big_int_signed_sub(pk_temp_1, &pk_temp_2);
            pk_0 = pk_1;
            ret_code += pk_temp_2.big_int_modulus(modulus, pk_1);
        }
    } while(temp_rem.big_int_is_zero() == false);

    if (prev_rem.big_int_compare(bi_1) != 0) {
        throw std::range_error("The numbers should be co-prime to find inverse.");
    }

    ret_code += pk_1.big_int_multiply(prev_quo[1], &pk_temp_1);
    ret_code += pk_0.big_int_signed_sub(pk_temp_1, &pk_temp_2);
    ret_code += pk_temp_2.big_int_modulus(modulus, pk_1);

    inverse = pk_1;
    return ret_code;

}

