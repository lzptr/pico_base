/** Minimal example for the segger systemviewer.
 *
 */

#include "SEGGER_RTT.h"
#include "SEGGER_SYSVIEW.h"
#include "hardware/irq.h"
#include "hardware/structs/systick.h"
#include "pico/stdlib.h"

#define LED_PIN PICO_DEFAULT_LED_PIN
#define BUTTON_PIN 22

extern void isr_systick()  // Rewrite of weak systick IRQ in crt0.s file
{
    SEGGER_SYSVIEW_RecordEnterISR();
    busy_wait_us(500);
    SEGGER_SYSVIEW_RecordExitISR();
}

void init_systick()
{
    systick_hw->csr = 0;            // Disable
    systick_hw->rvr = 124999999UL;  // Standard System clock (125Mhz)/ (rvr value + 1) = 1s
    systick_hw->csr = 0x7;          // Enable Systic, Enable Exceptions
}

void button_gpio_irq()
{
    SEGGER_SYSVIEW_RecordEnterISR();

    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, false);
    gpio_acknowledge_irq(BUTTON_PIN, GPIO_IRQ_EDGE_RISE);
    busy_wait_us(250);
    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true);
    SEGGER_SYSVIEW_RecordExitISR();
}

int main()
{
    static char r;
    stdio_init_all();
    init_systick();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_acknowledge_irq(BUTTON_PIN, GPIO_IRQ_EDGE_RISE);
    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true);
    gpio_add_raw_irq_handler(BUTTON_PIN, &button_gpio_irq);
    irq_set_enabled(IO_IRQ_BANK0, true);

    SEGGER_SYSVIEW_Conf();

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
