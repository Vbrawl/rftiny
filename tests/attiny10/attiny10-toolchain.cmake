
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(MCU "attiny10")
set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_ASM_COMPILER "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")
set(CMAKE_OBJCOPY "avr-objcopy")

set(CMAKE_C_FLAGS "-mmcu=attiny10 -Os -nostartfiles -Wl,--gc-sections")
set(CMAKE_CXX_FLAGS "-mmcu=attiny10 -Os -nostartfiles -Wl,--gc-sections")