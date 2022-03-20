#include "sd.h"
#include "hardware.h"
#include "util.h"

void sd_writeByte(byte c)
{
    PORT_SD_DATA = c;
    _SD_START_CLOCK
    __asm__("nop 5");
}

int sd_init()
{
    _sd_init_seq();
    byte result = sd_sendCMD0();
    _sd_waitForIdle();
}
void _sd_init_seq()
{
    _SD_PULLUP
    _SD_DISABLE
    delay(1);

    for (byte i = 0; i < 10; i++)
    {
        // Send FF
        sd_writeByte(0xFF);
    }

    _SD_ENABLE
    sd_writeByte(0xFF);
}
void _sd_waitForIdle() {}
