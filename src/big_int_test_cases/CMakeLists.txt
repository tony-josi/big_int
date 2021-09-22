
set(PYBIND_WRAPPER_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/big_int_test_cases")
set(PYBIND_WRAPPER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/big_int_test_cases/big_int_test_cases_inc")
set(TEST_CASES_SOURCE big_int_test_cases.cc)

add_library(big_int_tc_lib STATIC ${TEST_CASES_SOURCE})


target_link_libraries(
    big_int_tc_lib  
    project_options 
    project_warnings
    big_int_lib)

target_include_directories(
    big_int_tc_lib
    PRIVATE ${BI_LIB_INC_DIR}
    ${PYBIND_WRAPPER_INCLUDE_DIR}
)


pybind11_add_module (
    py_big_int_tc_wrap 
    ${PYBIND_WRAPPER_SOURCE_DIR}/py_tc_bindings.cc
)

target_link_libraries(
    py_big_int_tc_wrap 
    PUBLIC         
    big_int_tc_lib)

target_include_directories (
    py_big_int_tc_wrap 
    PRIVATE ${BI_LIB_INC_DIR}
    ${PYBIND_WRAPPER_INCLUDE_DIR}
)