/** Minimal example with segger RTT and JScope support.
 *
 * This example computes a sine wave and writes the floating point data to RTT channel 1.
 * Start the JScope appliaction after flashing the example and connect using a segger programmer.
 * It should automcaticall detect the RTT channel and the floating point varaible and plot the sine.
 */

#include <math.h>
#include <stdint.h>
#include "pico/stdlib.h"

int main(void)
{
    stdio_init_all();

    float amp = 1.0f;
    float sample_rate = 40000.0f;
    float freq = 10.0f;
    float dt = 1 / sample_rate;
    float theta = 0.0f;
    float two_pi = 2.0f * (float)M_PI;
    float theta_increment = two_pi * freq / sample_rate;
    float sine = 0.0f;
    float t = 0.0f;

    while (1)
    {
        sine = amp * sinf(theta);
        theta += theta_increment;
        if (theta > two_pi)
        {
            theta -= two_pi;
        }
        t += dt * 100u;
        printf("%f\t", t);
        printf("%.2f\n", sine);
    }
}