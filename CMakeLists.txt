cmake_minimum_required(VERSION 3.12)

project(rftiny)

enable_testing()
add_executable(test-rftiny tests/rftiny.c src/rftiny.c)
target_compile_options(test-rftiny PRIVATE -Os)
add_test(test-rftiny test-rftiny)