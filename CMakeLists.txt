cmake_minimum_required(VERSION 3.13)


include(pico_sdk_import.cmake)
project(pico_base_project C CXX ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps=cwd")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# Generate compile_commands.json for intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

add_subdirectory(src)

add_subdirectory(libs/segger)

add_subdirectory(examples/pico_rtt)
add_subdirectory(examples/pico_jscope)
add_subdirectory(examples/pico_systemview)
add_subdirectory(examples/pico_serialplot)