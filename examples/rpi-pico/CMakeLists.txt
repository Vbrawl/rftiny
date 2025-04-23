cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(rftiny-rpi-test)

pico_sdk_init()

add_executable(test-rpi-rftiny rftiny.c ../../src/rftiny.c)
target_compile_options(test-rpi-rftiny PRIVATE -Os)
target_link_libraries(test-rpi-rftiny pico_stdlib)
pico_enable_stdio_usb(test-rpi-rftiny 1)
pico_enable_stdio_uart(test-rpi-rftiny 0)
pico_add_extra_outputs(test-rpi-rftiny)