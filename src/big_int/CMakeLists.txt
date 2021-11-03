find_package (Threads)

set(BIG_INT_PRIV_INC_DIR "${PROJECT_SOURCE_DIR}/src/big_int/big_int_intrnl_inc")
set(SOURCES big_int.cc big_int_ctors_dtor.cc big_int_priv_defs.cc big_int_base_converter.cc)

add_library(big_int_lib STATIC ${SOURCES})


target_link_libraries(
    big_int_lib  
    project_options 
    project_warnings
    ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(
    big_int_lib
    PRIVATE ${BI_LIB_INC_DIR}
    ${BIG_INT_PRIV_INC_DIR}
)
