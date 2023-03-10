cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(pico_example C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Generate compile_commands.json for intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

add_subdirectory(src)
add_subdirectory(libs/segger)