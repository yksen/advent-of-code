cmake_minimum_required(VERSION 3.22)
project(aoc2024)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SOURCE_LIST src/*.cpp)

foreach(DAY IN ITEMS ${SOURCE_LIST})
    get_filename_component(TARGET_NAME ${DAY} NAME_WE)
    add_executable(${TARGET_NAME} ${DAY})
    target_include_directories(${TARGET_NAME} PRIVATE include)
    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_23)
endforeach()

add_custom_target(latest "${CMAKE_BINARY_DIR}/${TARGET_NAME}" DEPENDS ${TARGET_NAME})
