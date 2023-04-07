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

#define SCB_ICSR (*(volatile U32*)(0xE000ED04uL))  // Interrupt Control State Register
#define SCB_ICSR_PENDSTSET_MASK (1UL << 26)        // SysTick pending bit
extern unsigned int SEGGER_SYSVIEW_TickCnt;

void button_gpio_irq()
{
    SEGGER_SYSVIEW_RecordEnterISR();

    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, false);
    gpio_acknowledge_irq(BUTTON_PIN, GPIO_IRQ_EDGE_RISE);
    busy_wait_us(250);
    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true);
    SEGGER_SYSVIEW_RecordExitISR();
}

extern void isr_systick()  // Rewrite of weak systick IRQ in crt0.s file
{
    SEGGER_SYSVIEW_RecordEnterISR();
    SEGGER_SYSVIEW_TickCnt++;
    SEGGER_SYSVIEW_RecordExitISR();
}

void init_systick()
{
    systick_hw->csr = 0;         // Disable
    systick_hw->rvr = 124999UL;  // Standard System clock (125Mhz)/ (rvr value + 1) = 1us
    systick_hw->cvr = 0;         // clear the count to force initial reload
    systick_hw->csr = 0x7;       // Enable Systic, Enable Exceptions
}

/*********************************************************************
 *
 *       SEGGER_SYSVIEW_X_GetTimestamp()
 *
 * Function description
 *   Returns the current timestamp in ticks using the system tick
 *   count and the SysTick counter.
 *   All parameters of the SysTick have to be known and are set via
 *   configuration defines on top of the file.
 *
 * Return value
 *   The current timestamp.
 *
 * Additional information
 *   SEGGER_SYSVIEW_X_GetTimestamp is always called when interrupts are
 *   disabled. Therefore locking here is not required.
 */
uint32_t SEGGER_SYSVIEW_X_GetTimestamp(void)
{
    uint32_t tickCount;
    uint32_t timeStamp;
    uint32_t systick_counter_max;
    uint32_t systick_counter;

    // Read overflow counter
    tickCount = SEGGER_SYSVIEW_TickCnt;

    // SysTick is down-counting, subtract the current value from the number of cycles per tick.
    systick_counter_max = systick_hw->rvr + 1;
    systick_counter = (systick_counter_max - systick_hw->cvr);

    // If a timer interrupt is pending, adjust overflow counter
    if ((SCB_ICSR & SCB_ICSR_PENDSTSET_MASK) != 0)
    {
        systick_counter = (systick_counter_max - systick_hw->cvr);
        SEGGER_SYSVIEW_TickCnt++;
    }

    // Create combined 32-bit timestamp
    timeStamp = (tickCount << 16) | systick_counter;

    return timeStamp;
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
