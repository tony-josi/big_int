import sys
sys.path.append("/home/tony/Documents/Projects/big_int/build/src/big_int_test_cases")

from random_numbers import test_nums
import py_big_int_tc_wrap as pbitw

VERBOSE_LEVEL = 3

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

def test_1_bi_test_big_int_from_string(test_data):
    total_rand_nums = len(test_data)
    test_pass = 0
    test_fail = 0

    for i in range(total_rand_nums):
        if _bi_test_big_int_from_string(test_nums[i]):
            test_pass += 1
            _LOG_BI_TEST(2, "test_1_bi_test_big_int_from_string", "Test: {}, sub-test: {} = PASS".format("From string to bi", i))
        else:
            test_fail += 1
            _LOG_BI_TEST(2, "test_1_bi_test_big_int_from_string", "Test: {}, sub-test: {} = FAIL".format("From string to bi", i))

    _LOG_BI_TEST(1, "test_1_bi_test_big_int_from_string", "Total sub-test cases: {}, pass: {}".format(total_rand_nums, test_pass), optn = 1)



if __name__ == "__main__":

    test_1_bi_test_big_int_from_string(test_nums)

