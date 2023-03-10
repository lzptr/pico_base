/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "SEGGER_RTT.h"

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    static char r;
    stdio_init_all();
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n\r\n");
    SEGGER_RTT_WriteString(0, "###### Testing SEGGER_printf() ######\r\n");

    SEGGER_RTT_printf(0, "printf Test: %%c,         'S' : %c.\r\n", 'S');
    SEGGER_RTT_printf(0, "printf Test: %%5c,        'E' : %5c.\r\n", 'E');
    SEGGER_RTT_printf(0, "printf Test: %%-5c,       'G' : %-5c.\r\n", 'G');
    SEGGER_RTT_printf(0, "printf Test: %%5.3c,      'G' : %-5c.\r\n", 'G');
    SEGGER_RTT_printf(0, "printf Test: %%.3c,       'E' : %-5c.\r\n", 'E');
    SEGGER_RTT_printf(0, "printf Test: %%c,         'R' : %c.\r\n", 'R');
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
      
    }
#endif
}
