#include <math.h>
#include "SEGGER_RTT.h"
#include "pico/stdlib.h"

char RTT_UpBuffer[4096];  // J-Scope RTT Buffer
int RTT_Channel = 1;      // J-Scope RTT Channel

int main(void)
{
    SEGGER_RTT_ConfigUpBuffer(RTT_Channel, "JScope_f4", &RTT_UpBuffer[0], sizeof(RTT_UpBuffer),
                              SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    float sample_rate = 100.0f;
    float freq = 1.0f;
    float amp = 1.0f;
    const uint32_t N = (uint32_t)(sample_rate / freq) - 1;
    float sin_seq[100] = {0.0f};

    for (int i = 0; i < N; i++)
    {
        sin_seq[i] = amp * sinf(2.0f * (float)M_PI * freq * (float)i / sample_rate);
    }
    while (1)
    {
        for (int i = 0; i < N; i++)
        {
            SEGGER_RTT_Write(RTT_Channel, &sin_seq[i], sizeof(float));
            sleep_ms(10);
        }
    }
}
