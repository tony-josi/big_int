import sys
sys.path.append("/home/tony/Documents/Projects/big_int/build/src/big_int_test_cases")

from random_numbers import test_nums
import py_big_int_tc_wrap as pbitw

VERBOSE_LEVEL = 1

def _LOG_BI_TEST(verb_lvl, locn, str_data_1, str_data_2 = None, optn = 0):
    if verb_lvl <= VERBOSE_LEVEL:
        if(optn == 0):
            print("==> _LOG_BI_TEST: Location: {} Expected: {}, Actual: {}".format(locn, str_data_1, str_data_2))
        else:
            print("==> _LOG_BI_TEST: Location: {} Log: {}".format(locn, str_data_1))

def compare_hex_string_numbers(str_1, str_2):
    num_1 = int(str_1, 16)
    num_2 = int(str_2, 16)
    _LOG_BI_TEST(4, "compare_hex_string_numbers", num_1, num_2)
    if num_1 == num_2:
        return True
    else:
        return False

def _bi_test_big_int_from_string(num):
    hex_str = hex(num)[2:]
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_from_string(hex_str)
    _LOG_BI_TEST(3, "_bi_test_big_int_from_string", hex_str, ret_str)
    return compare_hex_string_numbers(ret_str, hex_str)

def _bi_test_big_int_unsigned_add(num_1, num_2):
    hex_str_1 = hex(num_1)[2:]
    hex_str_2 = hex(num_2)[2:]
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_unsigned_add(hex_str_1, hex_str_2)
    exp_res = hex(num_1 + num_2)[2:]
    _LOG_BI_TEST(3, "_bi_test_big_int_unsigned_add", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def _bi_test_big_int_unsigned_add_on_obj(num_1, num_2):
    hex_str_1 = hex(num_1)[2:]
    hex_str_2 = hex(num_2)[2:]
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_unsigned_add_on_obj(hex_str_1, hex_str_2)
    exp_res = hex(num_1 + num_2)[2:]
    _LOG_BI_TEST(3, "bi_test_big_int_unsigned_add_on_obj", exp_res, ret_str)
    return compare_hex_string_numbers(exp_res, ret_str)

def test_core_simple_loop(_test_func_, test_data):
    total_rand_nums = len(test_data)
    test_pass = 0
    test_fail = 0

    for i in range(total_rand_nums):
        if _test_func_(test_data[i]):
            test_pass += 1
            _LOG_BI_TEST(2, _test_func_.__name__, "Sub-test: {} = PASS".format(i))
        else:
            test_fail += 1
            _LOG_BI_TEST(2, _test_func_.__name__, "Sub-test: {} = FAIL".format(i))

    test_status = ""
    if(total_rand_nums == test_pass):
        test_status = "PASS"
    else:
        test_status = "FAIL"

    _LOG_BI_TEST(1, _test_func_.__name__, "Total sub-test cases: {}, pass: {} ==>>> **** {} ***".format(total_rand_nums, test_pass, test_status), optn = 1)

def test_core_2d_loop(_test_func_, test_data):
    total_rand_nums = len(test_data) * len(test_data)
    test_pass = 0
    test_fail = 0

    for j in range(len(test_data)):
        for i in range(len(test_data)):
            if _test_func_(test_data[j], test_data[i]):
                test_pass += 1
                _LOG_BI_TEST(2, _test_func_.__name__, "Sub-test: {} = PASS".format(i))
            else:
                test_fail += 1
                _LOG_BI_TEST(2, _test_func_.__name__, "Sub-test: {} = FAIL".format(i))
                _LOG_BI_TEST(1, _test_func_.__name__, "Input A: {} B: {}".format(test_data[j], test_data[i]))

    test_status = ""
    if(total_rand_nums == test_pass):
        test_status = "PASS"
    else:
        test_status = "FAIL"

    _LOG_BI_TEST(1, _test_func_.__name__, "Total sub-test cases: {}, pass: {} ==>>> **** {} ***".format(total_rand_nums, test_pass, test_status), optn = 1)

def test_1_bi_test_big_int_from_string(test_data):
    test_core_simple_loop(_bi_test_big_int_from_string, test_data)

def test_2_bi_test_big_int_unsigned_add(test_data):
    test_core_2d_loop(_bi_test_big_int_unsigned_add, test_data)

def test_3_bi_test_big_int_unsigned_add(test_data):
    test_core_2d_loop(_bi_test_big_int_unsigned_add_on_obj, test_data)


if __name__ == "__main__":

    test_1_bi_test_big_int_from_string(test_nums)
    test_2_bi_test_big_int_unsigned_add(test_nums)
    test_3_bi_test_big_int_unsigned_add(test_nums)

