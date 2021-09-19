

set(BI_LIB_INC_DIR "${PROJECT_SOURCE_DIR}/inc")

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(big_int)


#[[

find_package (Threads)

option(PROCESS_FILE_EXE "Build exe for file enc/dec" ON)
option(LOW_LEVEL_API_SAMPLE "Enable low level api sample" OFF)

if(LOW_LEVEL_API_SAMPLE)
    message("Builds low level API sample")
    set(SOURCES test_main.cpp)  
    add_executable(aes_sample_exe ${SOURCES})
    target_link_libraries(
        aes_sample_exe  
        project_options 
        project_warnings 
        aes_lib 
        ${CMAKE_THREAD_LIBS_INIT})
endif()

if(PROCESS_FILE_EXE)
    message("Builds exe for file enc/dec application")
    set(SOURCES process_file.cpp)  
    add_executable(aes_exe ${SOURCES})
    target_link_libraries(
        aes_exe  
        project_options 
        project_warnings 
        aes_lib 
        ${CMAKE_THREAD_LIBS_INIT})
endif()

]]