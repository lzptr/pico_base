add_executable(pico_serialplot main.c)

pico_enable_stdio_usb(pico_serialplot 1)
pico_enable_stdio_uart(pico_serialplot 0)
pico_add_extra_outputs(pico_serialplot)

# pull in common dependencies
target_compile_options(pico_serialplot PRIVATE -O0 -g3)
target_link_libraries(
  pico_serialplot PRIVATE pico_stdlib hardware_timer hardware_clocks
                                hardware_pwm segger_rtt)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_serialplot)
