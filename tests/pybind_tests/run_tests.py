import sys
sys.path.append("/home/tony/Documents/Projects/big_int/build/src/big_int_test_cases")

SIGNED_DATA_FPATH =     "/home/tony/Documents/Projects/big_int/tests/pybind_tests/signed_data.txt"
UNSIGNED_DATA_FPATH =   "/home/tony/Documents/Projects/big_int/tests/pybind_tests/unsigned_data.txt"

import py_big_int_tc_wrap as pbitw

VERBOSE_LEVEL = 1

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
                _LOG_BI_TEST(2, _test_func_.__name__, "Input A: {} B: {} = PASS".format(test_data[j], test_data[i]), optn = 1)
            else:
                test_fail += 1
                _LOG_BI_TEST(1, _test_func_.__name__, "Input A: {} B: {} = FAIL".format(test_data[j], test_data[i]), optn = 1)

    test_status = ""
    if(total_rand_nums == test_pass):
        test_status = "PASS"
    else:
        test_status = "FAIL"

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
        test_status = "PASS"
    else:
        test_status = "FAIL"

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

if __name__ == "__main__":

    if len(sys.argv) > 1:
        VERBOSE_LEVEL = int(sys.argv[1])

    test_nums_int = read_file_to_list(SIGNED_DATA_FPATH)
    test_nums_uint = read_file_to_list(UNSIGNED_DATA_FPATH)

    test_1_bi_test_big_int_from_string(test_nums_uint)
    test_2_bi_test_big_int_unsigned_add(test_nums_uint)
    test_3_bi_test_big_int_unsigned_add_on_obj(test_nums_uint)
    test_4_bi_test_big_int_unsigned_sub(test_nums_uint)
    test_5_bi_test_big_int_unsigned_sub_on_obj(test_nums_uint)
    test_6_bi_test_big_int_compare(test_nums_uint)
    test_7_bi_test_big_int_from_string_no_0x(test_nums_uint)
    test_8_bi_test_big_int_signed_add(test_nums_uint)

    test_1_bi_test_big_int_from_string(test_nums_int)
    test_2_bi_test_big_int_unsigned_add(test_nums_int)
    test_3_bi_test_big_int_unsigned_add_on_obj(test_nums_int)
    test_4_bi_test_big_int_unsigned_sub(test_nums_int)
    test_5_bi_test_big_int_unsigned_sub_on_obj(test_nums_int)
    test_6_bi_test_big_int_compare(test_nums_int)
    test_7_bi_test_big_int_from_string_no_0x(test_nums_int)
    test_8_bi_test_big_int_signed_add(test_nums_int)
