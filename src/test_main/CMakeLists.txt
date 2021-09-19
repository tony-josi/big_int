option(MAIN_TEST_EXE "Enable main test exe build" ON)

if(MAIN_TEST_EXE)
    message("Builds main test exe ")
    set(SOURCES main.cc)  
    add_executable(bi_test_exe ${SOURCES})
    target_link_libraries(
        bi_test_exe  
        project_options 
        project_warnings 
        big_int_lib)
endif()
