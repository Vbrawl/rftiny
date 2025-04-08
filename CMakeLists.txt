cmake_minimum_required(VERSION 3.12)

project(rftiny)

enable_testing()
add_executable(test-rftiny tests/rftiny.c src/rftiny.c)
target_compile_options(test-rftiny PRIVATE -Os)
add_test(test-rftiny test-rftiny)


add_executable(test-attiny10-rftiny tests/attiny10/rftiny.c src/rftiny.c)
target_compile_options(test-attiny10-rftiny PRIVATE -Os)

add_custom_command(
        TARGET test-attiny10-rftiny POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -j .text -j .data -O ihex $<TARGET_FILE:test-attiny10-rftiny> ${PROJECT_BINARY_DIR}/test-attiny10-rftiny.hex)