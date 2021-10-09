/** 
 *  @file   big_int_test_cases.hpp
 *  @brief  Header file for the big int test cases
 *
 *  This file contains the header code for big int test cases
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include <string>
#include "big_int.hpp"

class big_int_test_cases {

private:
    /* data */
public:
    std::string bi_test_big_int_from_string(const std::string &src_str);
    int         bi_test_big_int_compare(const std::string &a, const std::string &b);
    std::string bi_test_big_int_unsigned_add(const std::string &a, const std::string &b);
    std::string bi_test_big_int_unsigned_sub(const std::string &a, const std::string &b);
    std::string bi_test_big_int_unsigned_add_on_obj(const std::string &a, const std::string &b);
    std::string bi_test_big_int_unsigned_sub_on_obj(const std::string &a, const std::string &b);
    std::string bi_test_big_int_signed_add(const std::string &a, const std::string &b);
    std::string bi_test_big_int_signed_add_on_obj(const std::string &a, const std::string &b);
    std::string bi_test_big_int_left_shift_word_on_obj(const std::string &a, int shift_words);
    std::string bi_test_big_int_signed_sub(const std::string &a, const std::string &b);
    std::string bi_test_big_int_signed_sub_on_obj(const std::string &a, const std::string &b);
    std::string bi_test_big_int_unsigned_mulitply_258977(const std::string &a);
    std::string bi_test_big_int_multiply(const std::string &a, const std::string &b);
    int         bi_test_big_int_unsigned_compare(const std::string &a, const std::string &b);
    std::string bi_test_big_int_left_shift_on_obj(const std::string &a, int bits);
    std::string bi_test_big_int_left_shift_word(const std::string &a, int shift_words);
    std::string bi_test_big_int_left_shift(const std::string &a, int bits);
    std::string bi_test_big_int_right_shift_on_obj(const std::string &a, int bits);
    std::string bi_test_big_int_right_shift_word_on_obj(const std::string &a, int shift_words);
    std::string bi_test_big_int_right_shift_word(const std::string &a, int shift_words);
    std::string bi_test_big_int_right_shift(const std::string &a, int bits);
    int         bi_test_big_int_get_num_of_hex_chars(const std::string &a);
    std::string bi_test_big_int_from_base_type(const BI_BASE_TYPE &src_str, int is_neg);
    std::string bi_test_big_int_push_back_hex_chars(const std::string &src_str, BI_BASE_TYPE hex_char);
    int bi_test_big_int_divide_once_quotient(const std::string &a, const std::string &b);
    std::string bi_test_big_int_divide_once_remainder(const std::string &a, const std::string &b);
    
    int bi_test_big_int_divide(const std::string &dividend, const std::string &divisor);
    std::string bi_test_big_int_divide_quotient(const std::string &dividend, const std::string &divisor);
    std::string bi_test_big_int_divide_remainder(const std::string &dividend, const std::string &divisor);
    std::string bi_test_big_int_power_base_type(const std::string &base, const int &exponent);
    std::string bi_test_big_int_modulus(const std::string &num, const std::string &mod);

    std::string bi_test_big_int_modulus(const std::string &num, const std::string &mod);


};



