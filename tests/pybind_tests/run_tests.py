import py_big_int_tc_wrap as pbitw

if __name__ == "__main__":

    num_a = 0x1FFFFFFF1FFFFFFF
    num_b = 0x1FFFFFFF
    num_c = 0x4FFFFFFF1FFFFFFF

    test_obj = pbitw.big_int_tc()

    print("Test 1: Actual: ", test_obj.bi_test_big_int_from_string(str(num_a)[2:]), "Exp.: ", str(num_a)[2:])
