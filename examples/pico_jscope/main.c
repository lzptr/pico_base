/** Minimal example with segger RTT and JScope support.
 *
 * This example computes a sine wave and writes the floating point data to RTT channel 1.
 * Start the JScope appliaction after flashing the example and connect using a segger programmer.
 * It should automcaticall detect the RTT channel and the floating point varaible and plot the sine.
 */

#include <math.h>
#include <stdint.h>
#include "SEGGER_RTT.h"
#include "pico/stdlib.h"

char RTT_UpBuffer[1024u];  // J-Scope RTT Buffer
int RTT_Channel = 1u;      // J-Scope RTT Channel

int main(void)
{
    SEGGER_RTT_ConfigUpBuffer(RTT_Channel, "JScope_t4f4", &RTT_UpBuffer[0u], sizeof(RTT_UpBuffer),
                              SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    //
    // RTT block structure
    //
#pragma pack(push, 1)
    struct
    {
        uint32_t time_us;
        float sine;
    } rtt_buffer;
#pragma pack(pop)

    rtt_buffer.time_us = 0u;
    rtt_buffer.sine = 0.0f;

    float amp = 1.0f;
    float sample_rate = 40000.0f;
    float freq = 10.0f;
    float dt = 1 / sample_rate;
    float theta = 0.0f;
    float two_pi = 2.0f * (float)M_PI;
    float theta_increment = two_pi * freq / sample_rate;

    while (1)
    {
        rtt_buffer.sine = amp * sinf(theta);
        theta += theta_increment;
        if (theta > two_pi)
        {
            theta -= two_pi;
        }
        SEGGER_RTT_Write(RTT_Channel, &rtt_buffer, sizeof(rtt_buffer));
        rtt_buffer.time_us += dt * 1000u * 1000u;
    }
}