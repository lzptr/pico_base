add_executable(pico_systemview main.c SEGGER_SYSVIEW_Config_NoOS_CM0.c)

pico_enable_stdio_usb(pico_systemview 1)
pico_enable_stdio_uart(pico_systemview 0)
pico_add_extra_outputs(pico_systemview)


# pull in common dependencies
target_compile_options(pico_systemview PRIVATE -O0 -g3)
target_link_libraries(
  pico_systemview PRIVATE pico_stdlib hardware_timer hardware_clocks
                                hardware_pwm segger_systemview)

target_include_directories(pico_systemview PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_systemview)
