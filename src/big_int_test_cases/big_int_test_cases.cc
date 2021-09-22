/** 
 *  @file   big_int_test_cases.cc
 *  @brief  Source file for the big int test cases
 *
 *  This file contains the source code for big int test cases
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include "big_int_test_cases.hpp"
#include "big_int.hpp"

using namespace bi;

std::string big_int_test_cases::bi_test_big_int_from_string(const std::string &src_str) {

    big_int test_bi;
    test_bi.big_int_from_string(src_str);
    return test_bi.big_int_to_string(bi_base::BI_HEX);

}

std::string big_int_test_cases::bi_test_big_int_unsigned_add(const std::string &a, const std::string &b) {

    big_int test_bi_a, test_bi_b, test_bi_c;
    test_bi_a.big_int_from_string(a);
    test_bi_b.big_int_from_string(b);
    test_bi_a.big_int_unsigned_add(test_bi_b, &test_bi_c);
    return test_bi_c.big_int_to_string(bi_base::BI_HEX);

}
std::string big_int_test_cases::bi_test_big_int_unsigned_sub(const std::string &a, const std::string &b) {

    big_int test_bi_a, test_bi_b, test_bi_c;
    test_bi_a.big_int_from_string(a);
    test_bi_b.big_int_from_string(b);
    test_bi_a.big_int_unsigned_sub(test_bi_b, &test_bi_c);
    return test_bi_c.big_int_to_string(bi_base::BI_HEX);

}

std::string big_int_test_cases::bi_test_big_int_unsigned_add_on_obj(const std::string &a, const std::string &b) {

    big_int test_bi_a, test_bi_b;
    test_bi_a.big_int_from_string(a);
    test_bi_b.big_int_from_string(b);
    test_bi_a.big_int_unsigned_add(test_bi_b);
    return test_bi_a.big_int_to_string(bi_base::BI_HEX);

}

/*
std::string big_int_test_cases::bi_test_big_int_unsigned_sub_on_obj(const std::string &a, const std::string &b) {

    big_int test_bi_a, test_bi_b;
    test_bi_a.big_int_from_string(a);
    test_bi_b.big_int_from_string(b);
    test_bi_a.big_int_unsigned_sub(test_bi_b);
    return test_bi_a.big_int_to_string(bi_base::BI_HEX);

}
*/