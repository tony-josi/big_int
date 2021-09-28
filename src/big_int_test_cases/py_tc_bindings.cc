/** 
 *  @file   py_tc_bindings.cc
 *  @brief  Source file for the python bindings big int test cases
 *
 *  This file contains the source file for the python bindings 
 *  big int test cases.
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include "big_int_test_cases.hpp"
#include "pybind11/pybind11.h"

PYBIND11_MODULE(py_big_int_tc_wrap, module) {


	module.doc() = "Library for testing the big int api using python";


    pybind11::class_<big_int_test_cases>(module, "big_int_tc")
        .def(pybind11::init<>())
        .def("bi_test_big_int_from_string", &big_int_test_cases::bi_test_big_int_from_string, "bi_test_big_int_from_string test0", pybind11::arg("input"))
        .def("bi_test_big_int_compare", &big_int_test_cases::bi_test_big_int_compare)
        .def("bi_test_big_int_unsigned_add", &big_int_test_cases::bi_test_big_int_unsigned_add)
        .def("bi_test_big_int_unsigned_add_on_obj", &big_int_test_cases::bi_test_big_int_unsigned_add_on_obj)
        .def("bi_test_big_int_unsigned_sub", &big_int_test_cases::bi_test_big_int_unsigned_sub)
        .def("bi_test_big_int_unsigned_sub_on_obj", &big_int_test_cases::bi_test_big_int_unsigned_sub_on_obj)
        .def("bi_test_big_int_signed_add", &big_int_test_cases::bi_test_big_int_signed_add);

       
    //module.def("bi_test_big_int_from_string", &big_int_test_cases::bi_test_big_int_from_string, "bi_test_big_int_from_string test0");
}