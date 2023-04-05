add_executable(pico_rtt main.c)

pico_enable_stdio_usb(pico_rtt 1)
pico_enable_stdio_uart(pico_rtt 0)
pico_add_extra_outputs(pico_rtt)

# pull in common dependencies
target_compile_options(pico_rtt PRIVATE -O0 -g3)
target_link_libraries(
  pico_rtt PRIVATE pico_stdlib hardware_timer hardware_clocks segger_rtt)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_rtt)
