#ifndef _H_LCD
#define _H_LCD

#include "types.h"

void lcd_print(char *str);
void lcd_printchar(char c);
void lcd_wait();
void lcd_init();
void lcd_setbacklight(bool on);
void lcd_printByteAsHex(char c);
void lcd_printNybbleAsHex(char c);
void lcd_setCursor(bool on);
void lcd_clear();

#endif