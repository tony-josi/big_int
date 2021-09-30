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
    std::string bi_test_big_int_left_shift_word(const std::string &a, int shift_words);
    std::string bi_test_big_int_signed_sub(const std::string &a, const std::string &b);
    std::string bi_test_big_int_signed_sub_on_obj(const std::string &a, const std::string &b);
    std::string bi_test_big_int_unsigned_mulitply_258977(const std::string &a);

};



