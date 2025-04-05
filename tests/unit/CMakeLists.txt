cmake_minimum_required(VERSION 3.11)

project(mytest)
add_executable(mytest)

find_package(GTest REQUIRED)

target_include_directories(mytest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ../../inc
    sieve.h
)

target_sources(mytest PRIVATE
    ../../src/sieve.c
    test.c
)

target_link_libraries(mytest ${GTEST_LIBRARIES})

add_test(NAME gtest COMMAND gtest)