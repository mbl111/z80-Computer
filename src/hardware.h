#ifndef _H_HARDWARE
#define _H_HARDWARE

// #define interrupt __interrupt
// #define _asm __asm
// #define _endasm __endasm
// #define bit __bit
// #define code __code
// #define at __at

# define SFR(name, addr)        __sfr   __at(addr)                        name

static volatile SFR(PORT_LCD_CMD, 0x00);
static volatile SFR(PORT_LCD_DATA, 0x01);
static volatile SFR(PORTA, 0x10);

static volatile SFR(PORT_SD_DATA, 0x20);
static volatile SFR(PORT_SD_CLOCK, 0x21);
static volatile SFR(PORT_SD_DISABLE, 0x22);
static volatile SFR(PORT_SD_ENABLE, 0x23);

#define LCD_BACKLIGHT 0b00010000
#define IO_LED 0b01000000

#endif