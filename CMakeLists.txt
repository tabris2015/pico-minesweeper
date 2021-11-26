cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico-minesweeper C CXX ASM)
#set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(${PROJECT_NAME} main.cpp
        include/motor_bts7960.h
        src/motor_bts7960.cpp
        include/pins.h
        src/minesweeper.cpp
        include/minesweeper.h
        )

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        hardware_pwm
        hardware_timer
        )

pico_add_extra_outputs(${PROJECT_NAME})
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
