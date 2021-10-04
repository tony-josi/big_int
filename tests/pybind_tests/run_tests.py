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

import sys, random
sys.path.append("/home/tony/Documents/Projects/big_int/build/src/big_int_test_cases")

SIGNED_DATA_FPATH =     "/home/tony/Documents/Projects/big_int/tests/pybind_tests/signed_data.txt"
UNSIGNED_DATA_FPATH =   "/home/tony/Documents/Projects/big_int/tests/pybind_tests/unsigned_data.txt"

import py_big_int_tc_wrap as pbitw

VERBOSE_LEVEL = 1
SHIFT_WORDS_RANDINT_MAX = 5
SHIFT_BITS_RANDINT_MAX = 4048
RSHIFT_BITS_RANDINT_MAX = 128
UINT32_RANDINT_MAX = 0xFFFFFFFF
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
    num_1 = int(str_1, 16)
    num_2 = int(str_2, 16)
    _LOG_BI_TEST(4, "compare_hex_string_numbers", num_1, num_2)
    if num_1 == num_2:
        return True
    else:
        _LOG_BI_TEST(4, "compare_hex_string_numbers", num_1, num_2)
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
        _LOG_BI_TEST(1, "_bi_test_big_int_get_num_of_hex_chars", exp_val, ret_val)
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
    if num > 0:
        num += rand_num
    else:
        num -= rand_num
    exp_str = get_hex_str_without_0x(num)
    ret_str = test_obj.bi_test_big_int_push_back_hex_chars(hex_str, rand_num)
    _LOG_BI_TEST(3, "_bi_test_big_int_push_back_hex_chars", exp_str, ret_str)
    return compare_hex_string_numbers(ret_str, exp_str)

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
            _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} = FAIL".format(test_data[i]), optn = 1)

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
                _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} B: {} = FAIL".format(test_data[j], test_data[i]), optn = 1)

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

_bi_test_big_int_push_back_hex_chars

if __name__ == "__main__":

    if len(sys.argv) > 1:
        VERBOSE_LEVEL = int(sys.argv[1])

    test_nums_int = read_file_to_list(SIGNED_DATA_FPATH)
    test_nums_uint = read_file_to_list(UNSIGNED_DATA_FPATH)

    test_nums_int.append(0)
    test_nums_int.append(-1)
    test_nums_int.append(1)

    test_nums_uint.append(0)
    test_nums_uint.append(1)

    # test_1_bi_test_big_int_from_string(test_nums_uint)
    # test_2_bi_test_big_int_unsigned_add(test_nums_uint)
    # test_3_bi_test_big_int_unsigned_add_on_obj(test_nums_uint)
    # test_4_bi_test_big_int_unsigned_sub(test_nums_uint)
    # test_5_bi_test_big_int_unsigned_sub_on_obj(test_nums_uint)
    # test_6_bi_test_big_int_compare(test_nums_uint)
    # test_7_bi_test_big_int_from_string_no_0x(test_nums_uint)
    # test_8_bi_test_big_int_signed_add(test_nums_uint)
    # test_9_bi_test_big_int_signed_add_on_obj(test_nums_uint)
    # test_10_bi_test_big_int_left_shift_word_on_obj(test_nums_uint)
    # test_11_bi_test_big_int_signed_sub(test_nums_uint)
    # test_12_bi_test_big_int_signed_sub_on_obj(test_nums_uint)
    # test_13_bi_test_big_int_mulitply_258977(test_nums_uint)
    # test_14_bi_test_big_int_multiply(test_nums_uint)
    # test_15_bi_test_big_int_unsigned_compare(test_nums_uint)
    # test_16_bi_test_big_int_left_shift_on_obj(test_nums_uint)
    # test_17_bi_test_big_int_left_shift_word(test_nums_uint)
    # test_18_bi_test_big_int_left_shift(test_nums_uint)
    # test_19_bi_test_big_int_right_shift_on_obj(test_nums_uint)
    # test_20_bi_test_big_int_right_shift_word_on_obj(test_nums_uint)
    # test_21_bi_test_big_int_right_shift(test_nums_uint)
    # test_22_bi_test_big_int_right_shift_word(test_nums_uint)
    # test_23_bi_test_big_int_get_num_of_hex_chars(test_nums_uint)
    # test_24_bi_test_big_int_from_base_type(test_nums_uint)
    test_25_bi_test_big_int_push_back_hex_chars(test_nums_uint)

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
    test_23_bi_test_big_int_get_num_of_hex_chars(test_nums_uint)
    test_24_bi_test_big_int_from_base_type(test_nums_int)
    test_25_bi_test_big_int_push_back_hex_chars(test_nums_int)