cmake_minimum_required(VERSION 3.16)
project(AoC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Utils library
add_library(utils utils/utils.cpp)
target_include_directories(utils PUBLIC utils)

# Global input directory definition
set(INPUT_DIR "${CMAKE_SOURCE_DIR}/input")


# Find all day folders
file(GLOB DAY_DIRS day_*)

foreach(day_dir ${DAY_DIRS})
    file(GLOB DAY_SOURCES ${day_dir}/*.cpp)

    foreach(src ${DAY_SOURCES})
        get_filename_component(exec_name ${src} NAME_WE)
        add_executable(${exec_name} ${src})
        target_link_libraries(${exec_name} PRIVATE utils)
        target_compile_definitions(utils
            PUBLIC INPUT_DIR="${INPUT_DIR}"
        )
    endforeach()
endforeach()
