/** Minimal example for the segger systemviewer.
 *
 */

#include "SEGGER_RTT.h"
#include "SEGGER_SYSVIEW.h"
#include "pico/stdlib.h"
#include "hardware/structs/systick.h"

extern void isr_systick() //Rewrite of weak systick IRQ in crt0.s file
{
    SEGGER_SYSVIEW_RecordEnterISR();
    SEGGER_SYSVIEW_RecordExitISR();
}

void init_systick()
{ 
	systick_hw->csr = 0; 	    //Disable 
	systick_hw->rvr = 124999UL; //Standard System clock (125Mhz)/ (rvr value + 1) = 1ms 
    systick_hw->csr = 0x7;      //Enable Systic, Enable Exceptions	
}

int main()
{
    static char r;
    stdio_init_all();
    init_systick();

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
   
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
