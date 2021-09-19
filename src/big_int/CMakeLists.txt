
set(SOURCES big_int.cc)

add_library(big_int_lib STATIC ${SOURCES})


target_link_libraries(
    big_int_lib  
    project_options 
    project_warnings)

target_include_directories(
    big_int_lib
    PRIVATE ${BI_LIB_INC_DIR}
)
