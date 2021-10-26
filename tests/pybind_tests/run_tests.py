''' 
 @file   run_tests.py
 @brief  Main test src file

 This file contains the script that calls the test wrappers for the
 big_int library from the py_big_int_tc_wrap python module generated 
 by the pybind11.

 @author         Tony Josi   https://tonyjosi97.github.io/profile/
 @copyright      Copyright (C) 2021 Tony Josi
 @bug            No known bugs.
'''

import sys, random, math
sys.path.append("/home/tony/Documents/Projects/big_int/build/src/big_int_test_cases")

SIGNED_DATA_FPATH =     "/home/tony/Documents/Projects/big_int/tests/pybind_tests/signed_data.txt"
UNSIGNED_DATA_FPATH =   "/home/tony/Documents/Projects/big_int/tests/pybind_tests/unsigned_data.txt"

import py_big_int_tc_wrap as pbitw

VERBOSE_LEVEL = 1
SHIFT_WORDS_RANDINT_MAX = 5
SHIFT_BITS_RANDINT_MAX = 4048
RSHIFT_BITS_RANDINT_MAX = 128
UINT32_RANDINT_MAX = 0xFFFFFFFF
UINT32_EXPONENT_MAX = 0xF
MAX_HEX_CHAR = 0xF

PASS_STR_MESSAGE = "-- PASS --"
FAIL_STR_MESSAGE = "!!!!!!!!!!       FAIL      !!!!!!!!!!"

def _LOG_BI_TEST(verb_lvl, locn, str_data_1, str_data_2 = None, optn = 0):
    if verb_lvl <= VERBOSE_LEVEL:
        if(optn == 0):
            print("==> _LOG_BI_TEST: Location: {} Expected: {}, Actual: {}".format(locn, str_data_1, str_data_2))
        else:
            print("==> _LOG_BI_TEST: Location: {} Log: {}".format(locn, str_data_1))

def read_file_to_list(fpath):
    with open(fpath) as file:
        lines = file.readlines()
        des_list = [int(line.rstrip(), 10) for line in lines] 
        return des_list   

def get_hex_str_without_0x(num):
    num_str = hex(num)
    if num < 0:
        num_str = num_str[0] + num_str[3:]
    else:
        num_str = num_str[2:]
    return num_str

def compare_hex_string_numbers(str_1, str_2):
    # print(str_1, str_2)
    num_1 = int(str_1, 16)
    num_2 = int(str_2, 16)
    _LOG_BI_TEST(4, "compare_hex_string_numbers", num_1, num_2)
    if num_1 == num_2:
        return True
    else:
        _LOG_BI_TEST(1, "compare_hex_string_numbers", num_1, num_2)
        return False

def _bi_test_big_int_from_string(num):
    hex_str = get_hex_str_without_0x(num)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_from_string(hex_str)
    _LOG_BI_TEST(3, "_bi_test_big_int_from_string", hex_str, ret_str)
    return compare_hex_string_numbers(ret_str, hex_str)

def _bi_test_big_int_from_string_no_0x(num):
    hex_str = get_hex_str_without_0x(num)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_from_string(hex_str)
    _LOG_BI_TEST(3, "_bi_test_big_int_from_string", hex_str, ret_str)
    return compare_hex_string_numbers(ret_str, hex_str)

def _bi_test_big_int_unsigned_add(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_unsigned_add(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x((abs(num_1) + abs(num_2)))
    _LOG_BI_TEST(3, "_bi_test_big_int_unsigned_add", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_unsigned_add_on_obj(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_unsigned_add_on_obj(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x((abs(num_1) + abs(num_2)))

    if(num_1 < 0):
        # Catch thr case when the calling object is already -ve
        exp_res = '-' + exp_res
    _LOG_BI_TEST(3, "bi_test_big_int_unsigned_add_on_obj", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_unsigned_sub(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_unsigned_sub(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x(abs(num_1) - abs(num_2))
    _LOG_BI_TEST(3, "_bi_test_big_int_unsigned_add", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_unsigned_sub_on_obj(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_unsigned_sub_on_obj(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x(abs(num_1) - abs(num_2))

    if(num_1 < 0):
        # Catch thr case when the calling object is already -ve
        exp_res = '-' + exp_res
    _LOG_BI_TEST(3, "_bi_test_big_int_unsigned_add", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_compare(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_val = test_obj.bi_test_big_int_compare(hex_str_1, hex_str_2)
    act_comp_val = 0
    if num_1 > num_2:
        act_comp_val = 1
    elif num_1 < num_2:
        act_comp_val = -1
    _LOG_BI_TEST(3, "compare_big_int_numbers", num_1, num_2)
    return ret_val == act_comp_val

def _bi_test_big_int_signed_add(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_signed_add(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x(num_1 + num_2)
    _LOG_BI_TEST(3, "_bi_test_big_int_signed_add", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_signed_add_on_obj(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_signed_add_on_obj(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x(num_1 + num_2)
    _LOG_BI_TEST(3, "_bi_test_big_int_signed_add", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_left_shift_word_on_obj(num_1):
    shift_word_cnt = random.randint(0, SHIFT_WORDS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_left_shift_word_on_obj(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 << (shift_word_cnt * 32)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "_bi_test_big_int_left_shift_word_on_obj", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_left_shift_word(num_1):
    shift_word_cnt = random.randint(0, SHIFT_WORDS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_left_shift_word(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 << (shift_word_cnt * 32)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "_bi_test_big_int_left_shift_word_on_obj", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)


def _bi_test_big_int_signed_sub(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_signed_sub(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x(num_1 - num_2)
    _LOG_BI_TEST(3, "_bi_test_big_int_signed_sub", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_signed_sub_on_obj(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_signed_sub_on_obj(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x(num_1 - num_2)
    _LOG_BI_TEST(3, "_bi_test_big_int_signed_sub_on_obj", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_mulitply_258977(num_1):
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_unsigned_mulitply_258977(hex_str_1)
    exp_res = get_hex_str_without_0x(abs(num_1) * 258977)
    _LOG_BI_TEST(3, "_bi_test_big_int_mulitply_258977", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_multiply(num_1, num_2):
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_multiply(hex_str_1, hex_str_2)
    exp_res = get_hex_str_without_0x(num_1 * num_2)
    _LOG_BI_TEST(3, "_bi_test_big_int_multiply", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_unsigned_compare(num_1_ac, num_2_ac):
    num_1 = abs(num_1_ac)
    num_2 = abs(num_2_ac)
    hex_str_1 = get_hex_str_without_0x(num_1)
    hex_str_2 = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()
    ret_val = test_obj.bi_test_big_int_unsigned_compare(hex_str_1, hex_str_2)
    act_comp_val = 0
    if num_1 > num_2:
        act_comp_val = 1
    elif num_1 < num_2:
        act_comp_val = -1
    _LOG_BI_TEST(3, "_bi_test_big_int_unsigned_compare", num_1, num_2)
    return ret_val == act_comp_val

def _bi_test_big_int_left_shift_on_obj(num_1):
    shift_word_cnt = random.randint(0, SHIFT_BITS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_left_shift_on_obj(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 << (shift_word_cnt)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "bi_test_big_int_left_shift_on_obj {}".format(shift_word_cnt), exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_left_shift(num_1):
    shift_word_cnt = random.randint(0, SHIFT_BITS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_left_shift(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 << (shift_word_cnt)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "bi_test_big_int_left_shift_on_obj {}".format(shift_word_cnt), exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_right_shift_on_obj(num_1):

    if num_1 < 0:
        # To correct the arithmetic (python) vs logical (big_int lib) issue.
        num_1 *= -1

    shift_word_cnt = random.randint(0, RSHIFT_BITS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_right_shift_on_obj(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 >> (shift_word_cnt)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "bi_test_big_int_right_shift_on_obj {}: {}".format(shift_word_cnt, hex_str_1), exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_right_shift_word_on_obj(num_1):

    if num_1 < 0:
        # To correct the arithmetic (python) vs logical (big_int lib) issue.
        num_1 *= -1

    shift_word_cnt = random.randint(0, SHIFT_WORDS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_right_shift_word_on_obj(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 >> (shift_word_cnt * 32)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "bi_test_big_int_right_shift_word_on_obj {}".format(shift_word_cnt), exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_right_shift(num_1):

    if num_1 < 0:
        # To correct the arithmetic (python) vs logical (big_int lib) issue.
        num_1 *= -1

    shift_word_cnt = random.randint(0, RSHIFT_BITS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_right_shift(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 >> (shift_word_cnt)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "_bi_test_big_int_right_shift {}: {}".format(shift_word_cnt, hex_str_1), exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_right_shift_word(num_1):

    if num_1 < 0:
        # To correct the arithmetic (python) vs logical (big_int lib) issue.
        num_1 *= -1

    shift_word_cnt = random.randint(0, SHIFT_WORDS_RANDINT_MAX)
    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_right_shift_word(hex_str_1, shift_word_cnt)
    exp_res_num = num_1 >> (shift_word_cnt * 32)
    exp_res = get_hex_str_without_0x(exp_res_num)
    _LOG_BI_TEST(3, "_bi_test_big_int_right_shift_word {}".format(shift_word_cnt), exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_get_num_of_hex_chars(num_1):

    hex_str_1 = get_hex_str_without_0x(num_1)
    test_obj = pbitw.big_int_tc()
    ret_val = test_obj.bi_test_big_int_get_num_of_hex_chars(hex_str_1)
    if num_1 < 0:
        num_1 *= -1
    exp_val = len(get_hex_str_without_0x(num_1))
    _LOG_BI_TEST(3, "_bi_test_big_int_get_num_of_hex_chars", exp_val, ret_val)
    if (ret_val == exp_val):
        return True
    else:
        _LOG_BI_TEST(3, "_bi_test_big_int_get_num_of_hex_chars", exp_val, ret_val)
        return False

def _bi_test_big_int_from_base_type(num):
    rand_num = random.randint(-UINT32_RANDINT_MAX, UINT32_RANDINT_MAX)
    test_obj = pbitw.big_int_tc()
    urand_num = rand_num
    is_neg = 0
    if (rand_num < 0):
        urand_num = -1 * rand_num    
        is_neg = 1
    hex_str = get_hex_str_without_0x(rand_num)
    ret_str = test_obj.bi_test_big_int_from_base_type(urand_num, is_neg)
    _LOG_BI_TEST(3, "_bi_test_big_int_from_base_type", hex_str, ret_str)
    return compare_hex_string_numbers(ret_str, hex_str)

def _bi_test_big_int_push_back_hex_chars(num):
    rand_num = random.randint(0, MAX_HEX_CHAR)
    test_obj = pbitw.big_int_tc()
    hex_str = get_hex_str_without_0x(num)
    num <<= 4
    if num >= 0:
        num += rand_num
    else:
        num -= rand_num
    exp_str = get_hex_str_without_0x(num)
    ret_str = test_obj.bi_test_big_int_push_back_hex_chars(hex_str, rand_num)
    _LOG_BI_TEST(3, "_bi_test_big_int_push_back_hex_chars", exp_str, ret_str)
    return compare_hex_string_numbers(ret_str, exp_str)

def _bi_test_big_int_divide_once(num_1, num_2):
    num_1_abs = abs(num_1)
    num_2_abs = abs(num_2)
    hex_str_1 = get_hex_str_without_0x(num_1_abs)
    hex_str_2 = get_hex_str_without_0x(num_2_abs)

    if len(hex_str_1) != len(hex_str_2) or num_2 == 0:
        return True
    else:
        test_obj = pbitw.big_int_tc()
        quo = test_obj.bi_test_big_int_divide_once_quotient(hex_str_1, hex_str_2)
        rem = test_obj.bi_test_big_int_divide_once_remainder(hex_str_1, hex_str_2)
        exp_dividend = quo * num_2_abs + int(rem, 16)

        _LOG_BI_TEST(3, "_bi_test_big_int_divide_once_remainder: dividend: {}, divisor: {}, quo: {}, rem: {}, exp_dividend: {}".format(num_1_abs, num_2_abs, quo, int(rem, 16), exp_dividend), str_data_1 = None, optn = 1)

        if (exp_dividend == num_1_abs):
            return True
        else:
            return False

def _bi_test_big_int_divide(num_dividend, num_divisor):

    hex_str_divid = get_hex_str_without_0x(num_dividend)
    hex_str_divisr = get_hex_str_without_0x(num_divisor)

    test_obj = pbitw.big_int_tc()

    hex_str_exp_quo = ""
    hex_str_exp_rem = ""

    exp_ret_error = 0
    if num_divisor == 0:
        exp_ret_error = 1
    else:
        exp_quo = num_dividend // num_divisor
        exp_rem = num_dividend % num_divisor
        
        hex_str_exp_quo = get_hex_str_without_0x(exp_quo)
        hex_str_exp_rem = get_hex_str_without_0x(exp_rem)
    
    
    ret_status = test_obj.bi_test_big_int_divide(hex_str_divid, hex_str_divisr)
    quo_str = test_obj.bi_test_big_int_divide_quotient(hex_str_divid, hex_str_divisr)
    rem_str = test_obj.bi_test_big_int_divide_remainder(hex_str_divid, hex_str_divisr)

    _LOG_BI_TEST(3, "_bi_test_big_int_divide: dividend: {}, divisor: {}, quo: {}, rem: {}, exp_quo: {}, exp_rem: {}".\
        format(num_dividend, num_divisor, quo_str, rem_str, hex_str_exp_quo, hex_str_exp_rem), str_data_1 = None, optn = 1)

    if exp_ret_error == ret_status:
        if compare_hex_string_numbers(hex_str_exp_quo, quo_str) and compare_hex_string_numbers(hex_str_exp_rem, rem_str):
            return True
        return False
    elif exp_ret_error == 1:
        return True
    else:
        return False

def _bi_test_big_int_divide_signed(num_dividend, num_divisor):

    hex_str_divid = get_hex_str_without_0x(num_dividend)
    hex_str_divisr = get_hex_str_without_0x(num_divisor)

    test_obj = pbitw.big_int_tc()

    hex_str_exp_quo = ""
    hex_str_exp_rem = ""

    exp_ret_error = 0
    if num_divisor == 0:
        exp_ret_error = 1
    else:
        _quo = abs(num_dividend) // abs(num_divisor)
        _rem = abs(num_dividend) % abs(num_divisor)

        if num_dividend * num_divisor >= 0:
            exp_quo = _quo
        else:
            exp_quo = -1 * _quo

        exp_rem = _rem
        if num_dividend < 0:
            exp_rem = -1 * _rem
        
        
        hex_str_exp_quo = get_hex_str_without_0x(exp_quo)
        hex_str_exp_rem = get_hex_str_without_0x(exp_rem)
    
    
    ret_status = test_obj.bi_test_big_int_divide(hex_str_divid, hex_str_divisr)
    quo_str = test_obj.bi_test_big_int_divide_quotient(hex_str_divid, hex_str_divisr)
    rem_str = test_obj.bi_test_big_int_divide_remainder(hex_str_divid, hex_str_divisr)

    _LOG_BI_TEST(3, "_bi_test_big_int_divide: dividend: {}, divisor: {}, quo: {}, rem: {}, exp_quo: {}, exp_rem: {}".\
        format(num_dividend, num_divisor, quo_str, rem_str, hex_str_exp_quo, hex_str_exp_rem), str_data_1 = None, optn = 1)

    if exp_ret_error == ret_status:
        if compare_hex_string_numbers(hex_str_exp_quo, quo_str) and compare_hex_string_numbers(hex_str_exp_rem, rem_str):
            return True
        return False
    elif exp_ret_error == 1:
        return True
    else:
        return False

def _bi_test_big_int_power_base_type(num_1):

    rand_exp = random.randint(0, UINT32_EXPONENT_MAX)
    hex_str_base = get_hex_str_without_0x(num_1)

    test_obj = pbitw.big_int_tc()
    act_res = test_obj.bi_test_big_int_power_base_type(hex_str_base, rand_exp)
    hex_str_exp = get_hex_str_without_0x(pow(num_1, rand_exp))
    _LOG_BI_TEST(3, "_bi_test_big_int_power_base_type: exp: {}".format(rand_exp), hex_str_exp, act_res)
    if compare_hex_string_numbers(act_res, hex_str_exp):
        return True
    else:
        _LOG_BI_TEST(1, "_bi_test_big_int_power_base_type: exp: {}".format(rand_exp), hex_str_exp, act_res)
        return False

def _bi_test_big_int_modulus(num, mod):

    hex_str_num = get_hex_str_without_0x(num)
    hex_str_mod = get_hex_str_without_0x(mod)

    test_obj = pbitw.big_int_tc()

    hex_str_exp_quo = ""
    hex_str_exp_rem = ""

    if mod == 0:
        return True

    ret_str = test_obj.bi_test_big_int_modulus(hex_str_num, hex_str_mod)
    return compare_hex_string_numbers(get_hex_str_without_0x(num % mod), ret_str)
    
def _bi_test_big_int_fast_modular_exponentiation(base, exp, mod):
    
    if mod == 0:
        return True

    abs_base = base
    abs_exp = exp
    abs_mod = mod

    abs_base_str = get_hex_str_without_0x(abs_base)
    abs_exp_str = get_hex_str_without_0x(abs_exp)
    abs_mod_str = get_hex_str_without_0x(abs_mod)

    test_obj = pbitw.big_int_tc()
    act_res_str = test_obj.bi_test_big_int_fast_modular_exponentiation(abs_base_str, abs_exp_str, abs_mod_str)
    
    exp_res_str = ""
    try:
        exp_res_str = get_hex_str_without_0x(pow(abs_base, abs_exp, abs_mod))
    except Exception as _:
        if act_res_str == "NO_INV":
            _LOG_BI_TEST(3, "_bi_test_big_int_fast_modular_exponentiation: base {}, exp {}, mod {}".format(base, exp, mod), exp_res_str, act_res_str)
            return True

    _LOG_BI_TEST(3, "_bi_test_big_int_fast_modular_exponentiation: base {}, exp {}, mod {}".format(base, exp, mod), exp_res_str, act_res_str)
    return compare_hex_string_numbers(exp_res_str, act_res_str)

def _bi_test_big_int_gcd_euclidean_algorithm(num_1, num_2):

    exp_res = math.gcd(num_1, num_2)
    exp_res_str = get_hex_str_without_0x(exp_res)

    num_1_str = get_hex_str_without_0x(num_1)
    num_2_str = get_hex_str_without_0x(num_2)

    test_obj = pbitw.big_int_tc()
    act_res_str = test_obj.bi_test_big_int_gcd_euclidean_algorithm(num_1_str, num_2_str)
    _LOG_BI_TEST(3, "_bi_test_big_int_gcd_euclidean_algorithm", exp_res_str, act_res_str)
    return compare_hex_string_numbers(exp_res_str, act_res_str)

def _bi_test_big_int_modular_inverse_extended_euclidean_algorithm(num_1, num_2):

    num_1_str = get_hex_str_without_0x(num_1)
    num_2_str = get_hex_str_without_0x(num_2)

    test_obj = pbitw.big_int_tc()
    act_res_str = test_obj.bi_test_big_int_modular_inverse_extended_euclidean_algorithm(num_1_str, num_2_str)
    expected_inv_str = ""
    try:
        expected_inv_str = get_hex_str_without_0x(pow(num_1, -1, num_2))
    except Exception as _:
        if act_res_str == "NO_INV":
            _LOG_BI_TEST(3, "_bi_test_big_int_modular_inverse_extended_euclidean_algorithm: num_1 {}, num_2 {}".format(num_1, num_2), expected_inv_str, act_res_str)
            return True
    _LOG_BI_TEST(3, "_bi_test_big_int_modular_inverse_extended_euclidean_algorithm: num_1 {}, num_2 {}".format(num_1, num_2), expected_inv_str, act_res_str)
    return compare_hex_string_numbers(expected_inv_str, act_res_str)

def _bi_test_big_int_fast_divide_by_power_of_two(num_1):

    if (num_1 < 0):
        num_1 *= -1

    num_1_str = get_hex_str_without_0x(num_1)
    divid_pow = random.randint(0, RSHIFT_BITS_RANDINT_MAX)
    test_obj = pbitw.big_int_tc()

    exp_quo_str = get_hex_str_without_0x(num_1 // pow(2, divid_pow))
    exp_rem_str = get_hex_str_without_0x(num_1 % pow(2, divid_pow))
    
    act_res_quo_str = test_obj.bi_test_big_int_fast_divide_by_power_of_two_quotient(num_1_str, divid_pow)
    act_res_rem_str = test_obj.bi_test_big_int_fast_divide_by_power_of_two_remainder(num_1_str, divid_pow)
    _LOG_BI_TEST(3, "_bi_test_big_int_fast_divide_by_power_of_two: num_1 {}, pow {}".format(hex(num_1), divid_pow), exp_quo_str, act_res_quo_str)
    return compare_hex_string_numbers(exp_quo_str, act_res_quo_str) and compare_hex_string_numbers(exp_rem_str, act_res_rem_str)

def _bi_test_big_int_fast_multiply_by_power_of_two(num_1):

    num_1_str = get_hex_str_without_0x(num_1)
    divid_pow = random.randint(0, RSHIFT_BITS_RANDINT_MAX)
    test_obj = pbitw.big_int_tc()

    exp_pro_str = get_hex_str_without_0x(num_1 * pow(2, divid_pow))
    
    act_res_pro_str = test_obj.bi_test_big_int_fast_multiply_by_power_of_two(num_1_str, divid_pow)
    _LOG_BI_TEST(3, "_bi_test_big_int_fast_multiply_by_power_of_two: num_1 {}, pow {}".format(hex(num_1), divid_pow), exp_pro_str, act_res_pro_str)
    return compare_hex_string_numbers(exp_pro_str, act_res_pro_str)

def _bi_test_big_int_get_random_unsigned_between(num_1, num_2):

    if (num_1 < 0):
        num_1 *= -1
    if (num_2 < 0):
        num_2 *= -1

    if num_1 == num_2:
        return True
    
    if abs(num_1 - num_2) == 1:
        return True
    
    num_1_str = get_hex_str_without_0x(num_1)
    num_2_str = get_hex_str_without_0x(num_2)
    test_obj = pbitw.big_int_tc()

    _LOG_BI_TEST(3, "_bi_test_big_int_get_random_unsigned_between: num_1 {}, num_2 {}".format(hex(num_1), hex(num_2)), 0, 0)
    act_res_str = test_obj.bi_test_big_int_get_random_unsigned_between(num_1_str, num_2_str)
    
    if num_1 > num_2:
        return act_res_str == "RND_ERROR"
    else:
        if int(act_res_str, 16) >= num_1 and int(act_res_str, 16) < num_2:
            return True
        else:
            _LOG_BI_TEST(1, "_bi_test_big_int_get_random_unsigned_between: num_1 {}, num_2 {}".format(num_1, num_2), int(act_res_str, 16), int(act_res_str, 16))
            return False

def _bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded(bits):

    def isMillerRabinPassed(mrc):
        '''Run 20 iterations of Rabin Miller Primality test'''
        maxDivisionsByTwo = 0
        ec = mrc-1
        while ec % 2 == 0:
            ec >>= 1
            maxDivisionsByTwo += 1
        assert(2**maxDivisionsByTwo * ec == mrc-1)
    
        def trialComposite(round_tester):
            if pow(round_tester, ec, mrc) == 1:
                return False
            for i in range(maxDivisionsByTwo):
                if pow(round_tester, 2**i * ec, mrc) == mrc-1:
                    return False
            return True
    
        # Set number of trials here
        numberOfRabinTrials = 20
        for i in range(numberOfRabinTrials):
            round_tester = random.randrange(2, mrc)
            if trialComposite(round_tester):
                return False
        return True

    test_obj = pbitw.big_int_tc()
    exp_prime_str = test_obj.bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded(512, 20, -1)

    if isMillerRabinPassed(int(exp_prime_str, 16)):
        _LOG_BI_TEST(2, "_bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded: num_1 {} PASS".format(int(exp_prime_str, 16)), 0, 0)
        return True
    else:
        _LOG_BI_TEST(2, "_bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded: num_1 {} FAIL".format(int(exp_prime_str, 16)), 0, 0)
        return False

def test_core_simple_loop(_test_func_, test_data):
    total_rand_nums = len(test_data)
    test_pass = 0
    test_fail = 0

    for i in range(total_rand_nums):
        if _test_func_(test_data[i]):
            test_pass += 1
            _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} = PASS".format(test_data[i]), optn = 1)
        else:
            test_fail += 1
            _LOG_BI_TEST(1, _test_func_.__name__, "Input A: {} = FAIL".format(test_data[i]), optn = 1)

    test_status = ""
    if(total_rand_nums == test_pass):
        test_status = PASS_STR_MESSAGE
    else:
        test_status = FAIL_STR_MESSAGE

    _LOG_BI_TEST(1, _test_func_.__name__, "Total sub-test cases: {}, pass: {} ==>>> **** {} ***".format(total_rand_nums, test_pass, test_status), optn = 1)

def test_core_2d_loop(_test_func_, test_data):
    total_rand_nums = len(test_data) * len(test_data)
    test_pass = 0
    test_fail = 0

    for j in range(len(test_data)):
        for i in range(len(test_data)):
            if _test_func_(test_data[j], test_data[i]):
                test_pass += 1
                _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} B: {} = PASS".format(test_data[j], test_data[i]), optn = 1)
            else:
                test_fail += 1
                _LOG_BI_TEST(1, _test_func_.__name__, "Input A: {} B: {} = FAIL".format(test_data[j], test_data[i]), optn = 1)

    test_status = ""
    if(total_rand_nums == test_pass):
        test_status = PASS_STR_MESSAGE
    else:
        test_status = FAIL_STR_MESSAGE

    _LOG_BI_TEST(1, _test_func_.__name__, "Total sub-test cases: {}, pass: {} ==>>> **** {} ***".format(total_rand_nums, test_pass, test_status), optn = 1)

def test_core_2d_loop_compare(_test_func_, test_data):
    total_rand_nums = 0
    test_pass = 0
    test_fail = 0

    for j in range(len(test_data)):
        for i in range(len(test_data)):
            if (abs(test_data[j]) >= abs(test_data[i])):
                total_rand_nums += 1
                res = _test_func_(test_data[j], test_data[i])
                if res:
                    test_pass += 1
                    _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} B: {} = PASS".format(test_data[j], test_data[i]), optn = 1)
                else:
                    test_fail += 1
                    _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} B: {} = FAIL".format(test_data[j], test_data[i]), optn = 1)

    test_status = ""
    if(total_rand_nums == test_pass):
        test_status = PASS_STR_MESSAGE
    else:
        test_status = FAIL_STR_MESSAGE

    _LOG_BI_TEST(1, _test_func_.__name__, "Total sub-test cases: {}, pass: {} ==>>> **** {} ***".format(total_rand_nums, test_pass, test_status), optn = 1)

def test_core_3d_loop(_test_func_, test_data_list, test_cases_div):
    total_tc_from_list = len(test_data_list) // test_cases_div
    total_rand_nums = total_tc_from_list ** 3
    test_data = test_data_list[:total_tc_from_list]
    test_pass = 0
    test_fail = 0

    for j in range(len(test_data)):
        for i in range(len(test_data)):
            for k in range(len(test_data)):
                #_LOG_BI_TEST(1, _test_func_.__name__, "Input A: {} B: {} C: {}= FAIL".format(test_data[j], test_data[i], test_data[k]), optn = 1)
                if _test_func_(test_data[j], test_data[i], test_data[k]):
                    test_pass += 1
                    _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} B: {} C: {}= PASS".format(test_data[j], test_data[i], test_data[k]), optn = 1)
                else:
                    test_fail += 1
                    _LOG_BI_TEST(1, _test_func_.__name__, "Input A: {} B: {} C: {}= FAIL".format(test_data[j], test_data[i], test_data[k]), optn = 1)

    test_status = ""
    if(total_rand_nums == test_pass):
        test_status = PASS_STR_MESSAGE
    else:
        test_status = FAIL_STR_MESSAGE

    _LOG_BI_TEST(1, _test_func_.__name__, "Total sub-test cases: {}, pass: {} ==>>> **** {} ***".format(total_rand_nums, test_pass, test_status), optn = 1)

def test_1_bi_test_big_int_from_string(test_data):
    test_core_simple_loop(_bi_test_big_int_from_string, test_data)

def test_2_bi_test_big_int_unsigned_add(test_data):
    test_core_2d_loop(_bi_test_big_int_unsigned_add, test_data)

def test_3_bi_test_big_int_unsigned_add_on_obj(test_data):
    test_core_2d_loop(_bi_test_big_int_unsigned_add_on_obj, test_data)

def test_4_bi_test_big_int_unsigned_sub(test_data):
    test_core_2d_loop_compare(_bi_test_big_int_unsigned_sub, test_data)

def test_5_bi_test_big_int_unsigned_sub_on_obj(test_data):
    test_core_2d_loop_compare(_bi_test_big_int_unsigned_sub_on_obj, test_data)

def test_6_bi_test_big_int_compare(test_data):
    test_core_2d_loop(_bi_test_big_int_compare, test_data)

def test_7_bi_test_big_int_from_string_no_0x(test_data):
    test_core_simple_loop(_bi_test_big_int_from_string_no_0x, test_data)

def test_8_bi_test_big_int_signed_add(test_data):
    test_core_2d_loop(_bi_test_big_int_signed_add, test_data)

def test_9_bi_test_big_int_signed_add_on_obj(test_data):
    test_core_2d_loop(_bi_test_big_int_signed_add_on_obj, test_data)

def test_10_bi_test_big_int_left_shift_word_on_obj(test_data):
    test_core_simple_loop(_bi_test_big_int_left_shift_word_on_obj, test_data)

def test_11_bi_test_big_int_signed_sub(test_data):
    test_core_2d_loop(_bi_test_big_int_signed_sub, test_data)

def test_12_bi_test_big_int_signed_sub_on_obj(test_data):
    test_core_2d_loop(_bi_test_big_int_signed_sub_on_obj, test_data)

def test_13_bi_test_big_int_mulitply_258977(test_data):
    test_core_simple_loop(_bi_test_big_int_mulitply_258977, test_data)

def test_14_bi_test_big_int_multiply(test_data):
    test_core_2d_loop(_bi_test_big_int_multiply, test_data)

def test_15_bi_test_big_int_unsigned_compare(test_data):
    test_core_2d_loop(_bi_test_big_int_unsigned_compare, test_data)

def test_16_bi_test_big_int_left_shift_on_obj(test_data):
    test_core_simple_loop(_bi_test_big_int_left_shift_on_obj, test_data)

def test_17_bi_test_big_int_left_shift_word(test_data):
    test_core_simple_loop(_bi_test_big_int_left_shift_word, test_data)

def test_18_bi_test_big_int_left_shift(test_data):
    test_core_simple_loop(_bi_test_big_int_left_shift, test_data)

def test_19_bi_test_big_int_right_shift_on_obj(test_data):
    test_core_simple_loop(_bi_test_big_int_right_shift_on_obj, test_data)

def test_20_bi_test_big_int_right_shift_word_on_obj(test_data):
    test_core_simple_loop(_bi_test_big_int_right_shift_word_on_obj, test_data)

def test_21_bi_test_big_int_right_shift(test_data):
    test_core_simple_loop(_bi_test_big_int_right_shift, test_data)

def test_22_bi_test_big_int_right_shift_word(test_data):
    test_core_simple_loop(_bi_test_big_int_right_shift_word, test_data)

def test_23_bi_test_big_int_get_num_of_hex_chars(test_data):
    test_core_simple_loop(_bi_test_big_int_get_num_of_hex_chars, test_data)

def test_24_bi_test_big_int_from_base_type(test_data):
    test_core_simple_loop(_bi_test_big_int_from_base_type, test_data)

def test_25_bi_test_big_int_push_back_hex_chars(test_data):
    test_core_simple_loop(_bi_test_big_int_push_back_hex_chars, test_data)

def test_26_bi_test_big_int_divide_once(test_data):
    test_core_2d_loop(_bi_test_big_int_divide_once, test_data)

def test_27_bi_test_big_int_divide(test_data):
    test_core_2d_loop(_bi_test_big_int_divide, test_data)

def test_27_bi_test_big_int_divide_signed(test_data):
    test_core_2d_loop(_bi_test_big_int_divide_signed, test_data)

def test_28_bi_test_big_int_power_base_type(test_data):
    test_core_simple_loop(_bi_test_big_int_power_base_type, test_data)

def test_29_bi_test_big_int_modulus(test_data):
    test_core_2d_loop(_bi_test_big_int_modulus, test_data)

def test_30_bi_test_big_int_fast_modular_exponentiation(test_data):
    test_core_3d_loop(_bi_test_big_int_fast_modular_exponentiation, test_data, 10)

def test_31_bi_test_big_int_gcd_euclidean_algorithm(test_data):
    test_core_2d_loop(_bi_test_big_int_gcd_euclidean_algorithm, test_data)

def test_32_bi_test_big_int_modular_inverse_extended_euclidean_algorithm(test_data):
    test_core_2d_loop(_bi_test_big_int_modular_inverse_extended_euclidean_algorithm, test_data)

def test_33_bi_test_big_int_fast_divide_by_power_of_two(test_data):
    test_core_simple_loop(_bi_test_big_int_fast_divide_by_power_of_two, test_data)

def test_34_bi_test_big_int_fast_divide_by_power_of_two(test_data):
    test_core_simple_loop(_bi_test_big_int_fast_multiply_by_power_of_two, test_data)

def test_35_bi_test_big_int_get_random_unsigned_between(test_data):
    test_core_2d_loop(_bi_test_big_int_get_random_unsigned_between, test_data)

def test_36_bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded(test_iterations):
    pass_cntr = 0
    for _ in range(test_iterations):
        if _bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded(512):
            pass_cntr += 1
    if(pass_cntr == test_iterations):
        test_status = PASS_STR_MESSAGE
    else:
        test_status = FAIL_STR_MESSAGE

    _LOG_BI_TEST(1, _bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded.__name__, "Total sub-test cases: {}, pass: {} ==>>> **** {} ***".format(test_iterations, pass_cntr, test_status), optn = 1)

if __name__ == "__main__":

    if len(sys.argv) > 1:
        VERBOSE_LEVEL = int(sys.argv[1])

    test_nums_int = read_file_to_list(SIGNED_DATA_FPATH)
    test_nums_uint = read_file_to_list(UNSIGNED_DATA_FPATH)

    test_nums_int[3:] = test_nums_int
    test_nums_int[0] = 0
    test_nums_int[1] = -1
    test_nums_int[2] = 1

    test_nums_uint[2:] = test_nums_uint
    test_nums_int[0] = 0
    test_nums_int[1] = 1

    test_1_bi_test_big_int_from_string(test_nums_uint)
    test_2_bi_test_big_int_unsigned_add(test_nums_uint)
    test_3_bi_test_big_int_unsigned_add_on_obj(test_nums_uint)
    test_4_bi_test_big_int_unsigned_sub(test_nums_uint)
    test_5_bi_test_big_int_unsigned_sub_on_obj(test_nums_uint)
    test_6_bi_test_big_int_compare(test_nums_uint)
    test_7_bi_test_big_int_from_string_no_0x(test_nums_uint)
    test_8_bi_test_big_int_signed_add(test_nums_uint)
    test_9_bi_test_big_int_signed_add_on_obj(test_nums_uint)
    test_10_bi_test_big_int_left_shift_word_on_obj(test_nums_uint)
    test_11_bi_test_big_int_signed_sub(test_nums_uint)
    test_12_bi_test_big_int_signed_sub_on_obj(test_nums_uint)
    test_13_bi_test_big_int_mulitply_258977(test_nums_uint)
    test_14_bi_test_big_int_multiply(test_nums_uint)
    test_15_bi_test_big_int_unsigned_compare(test_nums_uint)
    test_16_bi_test_big_int_left_shift_on_obj(test_nums_uint)
    test_17_bi_test_big_int_left_shift_word(test_nums_uint)
    test_18_bi_test_big_int_left_shift(test_nums_uint)
    test_19_bi_test_big_int_right_shift_on_obj(test_nums_uint)
    test_20_bi_test_big_int_right_shift_word_on_obj(test_nums_uint)
    test_21_bi_test_big_int_right_shift(test_nums_uint)
    test_22_bi_test_big_int_right_shift_word(test_nums_uint)
    test_23_bi_test_big_int_get_num_of_hex_chars(test_nums_uint)
    test_24_bi_test_big_int_from_base_type(test_nums_uint)
    test_25_bi_test_big_int_push_back_hex_chars(test_nums_uint)
    test_26_bi_test_big_int_divide_once(test_nums_uint)
    test_27_bi_test_big_int_divide(test_nums_uint)
    test_28_bi_test_big_int_power_base_type(test_nums_uint)
    test_29_bi_test_big_int_modulus(test_nums_uint)
    test_30_bi_test_big_int_fast_modular_exponentiation(test_nums_uint)
    test_31_bi_test_big_int_gcd_euclidean_algorithm(test_nums_uint)
    test_32_bi_test_big_int_modular_inverse_extended_euclidean_algorithm(test_nums_uint)
    test_33_bi_test_big_int_fast_divide_by_power_of_two(test_nums_uint)
    test_34_bi_test_big_int_fast_divide_by_power_of_two(test_nums_uint)
    test_35_bi_test_big_int_get_random_unsigned_between(test_nums_uint) 

    test_1_bi_test_big_int_from_string(test_nums_int)
    test_2_bi_test_big_int_unsigned_add(test_nums_int)
    test_3_bi_test_big_int_unsigned_add_on_obj(test_nums_int)
    test_4_bi_test_big_int_unsigned_sub(test_nums_int)
    test_5_bi_test_big_int_unsigned_sub_on_obj(test_nums_int)
    test_6_bi_test_big_int_compare(test_nums_int)
    test_7_bi_test_big_int_from_string_no_0x(test_nums_int)
    test_8_bi_test_big_int_signed_add(test_nums_int)
    test_9_bi_test_big_int_signed_add_on_obj(test_nums_int)
    test_10_bi_test_big_int_left_shift_word_on_obj(test_nums_int)
    test_11_bi_test_big_int_signed_sub(test_nums_int)
    test_12_bi_test_big_int_signed_sub_on_obj(test_nums_int)
    test_13_bi_test_big_int_mulitply_258977(test_nums_int)
    test_14_bi_test_big_int_multiply(test_nums_int)
    test_15_bi_test_big_int_unsigned_compare(test_nums_int)
    test_16_bi_test_big_int_left_shift_on_obj(test_nums_int)
    test_17_bi_test_big_int_left_shift_word(test_nums_int)
    test_18_bi_test_big_int_left_shift(test_nums_int)
    test_19_bi_test_big_int_right_shift_on_obj(test_nums_int)
    test_20_bi_test_big_int_right_shift_word_on_obj(test_nums_int)
    test_21_bi_test_big_int_right_shift(test_nums_int)
    test_22_bi_test_big_int_right_shift_word(test_nums_int)
    test_23_bi_test_big_int_get_num_of_hex_chars(test_nums_int)
    test_24_bi_test_big_int_from_base_type(test_nums_int)
    test_25_bi_test_big_int_push_back_hex_chars(test_nums_int)
    test_26_bi_test_big_int_divide_once(test_nums_int)
    test_27_bi_test_big_int_divide_signed(test_nums_int)
    test_28_bi_test_big_int_power_base_type(test_nums_int)
    test_29_bi_test_big_int_modulus(test_nums_int)
    test_30_bi_test_big_int_fast_modular_exponentiation(test_nums_int)
    test_31_bi_test_big_int_gcd_euclidean_algorithm(test_nums_int)
    test_32_bi_test_big_int_modular_inverse_extended_euclidean_algorithm(test_nums_int)
    test_33_bi_test_big_int_fast_divide_by_power_of_two(test_nums_int)
    test_34_bi_test_big_int_fast_divide_by_power_of_two(test_nums_int)
    test_35_bi_test_big_int_get_random_unsigned_between(test_nums_int)  
     
    test_36_bi_test_big_int_get_random_unsigned_prime_rabin_miller_threaded(10)
      
    # print(_bi_test_big_int_divide(0xfdbeef123beefdeaaaddee, 0xdeed))
    # print(_bi_test_big_int_power_base_type(0xfdbeef123beefdeaaaddee))
    # print(_bi_test_big_int_fast_modular_exponentiation(0xfdbeef123beefdeaaaddee, 0xfdbe, 0xfdbeef123beefdeaaa))
    # print(_bi_test_big_int_gcd_euclidean_algorithm(64958, 16629248))
    # print(_bi_test_big_int_modular_inverse_extended_euclidean_algorithm(1368960011, 4283773211))
    