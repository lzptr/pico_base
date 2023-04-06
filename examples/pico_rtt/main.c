/** Minimal example with segger RTT.
 *
 * Select the RTT_Console launch configuration, to set up the RTT console configuration for vs code/cortex-debug.
 * The RTT console is opened in another terminal window in vs code.
 */

#include "SEGGER_RTT.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define LED_PIN PICO_DEFAULT_LED_PIN

int main()
{
    static char r;
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    uint32_t freq = clock_get_hz(clk_sys);
    SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n\r\n");
    SEGGER_RTT_WriteString(0, "###### Testing SEGGER_printf() ######\r\n");

    int counter = 0;
    while (true)
    {
        gpio_put(LED_PIN, 1);
        sleep_us(250000);
        gpio_put(LED_PIN, 0);
        sleep_us(250000);

        SEGGER_RTT_printf(0, "LED Cycle: %d\n", counter++);
    }
}
