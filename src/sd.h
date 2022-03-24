#ifndef _H_SD
#define _H_SD

#include "hardware.h"
#include "types.h"

#define _SD_START_CLOCK __asm out(_PORT_SD_CLOCK), a __endasm;
#define _SD_ENABLE __asm out(_PORT_SD_ENABLE), a __endasm;
#define _SD_DISABLE __asm out(_PORT_SD_DISABLE), a __endasm;

#define _SD_PULLUP __asm in a, (_PORT_SD_ENABLE)__endasm;
#define _SD_PULLDOWN __asm in a, (_PORT_SD_DISABLE)__endasm;

void sd_writeByte(byte c);
byte sd_readByte();
int sd_init();
void _sd_init_seq();
void _sd_waitForIdle();

byte sd_sendCMD0();
void sd_sendCMD8();
void sd_sendCMD58();
void sd_sendACMD41();

byte sd_readR1();
byte sd_readR7();
byte sd_readR3();

#endif