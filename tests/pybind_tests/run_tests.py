import sys
sys.path.append("/home/tony/Documents/Projects/big_int/build/src/big_int_test_cases")

import py_big_int_tc_wrap as pbitw

VERBOSE_LEVEL = 2

def _LOG_BI_TEST(verb_lvl, str_data_1, str_data_2 = None, optn = 0):
    if verb_lvl <= VERBOSE_LEVEL:
        if(optn == 0):
            print("==> _LOG_BI_TEST: Expected: {}, Actual: {}".format(str_data_1, str_data_2))
        else:
            print(str_data_1)

def compare_hex_string_numbers(str_1, str_2):
    num_1 = int(str_1, 16)
    num_2 = int(str_2, 16)
    _LOG_BI_TEST(3, num_1, num_2)
    if num_1 == num_2:
        return True
    else:
        return False

def _bi_test_big_int_from_string(num):
    hex_str = hex(num)[2:]
    test_obj = pbitw.big_int_tc()
    ret_str = test_obj.bi_test_big_int_from_string(hex_str)
    _LOG_BI_TEST(1, hex_str, ret_str)
    if compare_hex_string_numbers(ret_str, hex_str):
        return True
    else:
        return True


if __name__ == "__main__":

    num_a = 0x1FFFFFFF1FFFFFFF
    num_b = 0x1FFFFFFF
    num_c = 0x4FFFFFFF1FFFFFFF

    _bi_test_big_int_from_string(num_a)
