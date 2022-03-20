#include "lcd.h"
#include "hardware.h"

//#define PORT_LCD_CMD dummy0x

#define LCD_CMD_CLEAR_DISPLAY 0x01
#define LCD_CMD_RETURN_HOME 0x02
#define LCD_CMD_ENTRY_MODE 0x04
#define LCD_CMD_DISPLAY_ON_OFF 0x08
#define LCD_CMD_CURSOR_SHIFT 0x10
#define LCD_CMD_FUNCTION 0x20
#define LCD_CMD_SET_CGRAM_ADDRESS 0x40
#define LCD_CMD_SET_DRAM_ADDRESS 0x80

//;Display Entry Mode
#define LCD_ENTRY_SHIFT 0x01
#define LCD_ENTRY_NO_SHIFT 0x00
#define LCD_ENTRY_INC 0x02
#define LCD_ENTRY_DEC 0x00

//;Display On/Off Control0x
#define LCD_DISPLAY_ON 0x04
#define LCD_CURSOR_ON 0x02
#define LCD_CURSOR_BLINK 0x01

//;Cursor or Display Shift0x
#define LCD_SHIFT_CURSOR 0x08
#define LCD_SHIFT_DIR_RIGHT 0x04

//;Function Set0x
#define LCD_FUNCTION_MODE_4B 0x00
#define LCD_FUNCTION_MODE_8B 0x10
#define LCD_FUNCTION_2_LINES 0x08
#define LCD_FUNCTION_1_LINE 0x00
#define LCD_FUNCTION_FONT_5x11 0x04
#define LCD_FUNCTION_FONT_5x8 0x00

//;CURSOR POSITIONING0x
#define LCD_LINE_1 0x00
#define LCD_LINE_2 0x40

#define LCD_STATUS_BUSY 0x80

#define LCD_INIT_DATA_LENGTH 4

unsigned char LCD_CURSOR_STATE = 0;

// Waits for the LCD busy flag to be false so we can send data to it
void lcd_wait()
{
	while (PORT_LCD_CMD & LCD_STATUS_BUSY)
	{
		// Wait for LDC To not be busy
	}
}

// Prints a null terminated string to the LDC
void lcd_print(char *str)
{
	while (*str != 0x00)
	{
		lcd_printchar(*str++);
	}
}

void lcd_printchar(char c)
{
	lcd_wait();
	PORT_LCD_DATA = c;
}

void lcd_init()
{
	// unsigned char initData[] = {0x3F, 0x0F, 0x01, 0x06};
	lcd_wait();
	PORT_LCD_CMD = LCD_CMD_FUNCTION | LCD_FUNCTION_MODE_8B | LCD_FUNCTION_2_LINES | LCD_FUNCTION_FONT_5x8;

	lcd_setDisplay(true);
	lcd_setCursor(true);
	lcd_clear();

	lcd_wait();
	PORT_LCD_CMD = LCD_CMD_ENTRY_MODE | LCD_ENTRY_NO_SHIFT | LCD_ENTRY_INC;
}

void lcd_clear()
{
	lcd_wait();
	PORT_LCD_CMD = LCD_CMD_CLEAR_DISPLAY;
}

// This function assumes the display is on
void lcd_setCursor(bool on)
{
	lcd_wait();
	if (on)
		LCD_CURSOR_STATE |= LCD_CURSOR_ON | LCD_CURSOR_BLINK;
	else
		LCD_CURSOR_STATE &= 0b11111100;

	PORT_LCD_CMD = LCD_CMD_DISPLAY_ON_OFF | LCD_CURSOR_STATE;
}

void lcd_setDisplay(bool on)
{
	lcd_wait();
	if (on)
		LCD_CURSOR_STATE |= LCD_DISPLAY_ON;
	else
		LCD_CURSOR_STATE &= 0b11111011;

	PORT_LCD_CMD = LCD_CMD_DISPLAY_ON_OFF | LCD_CURSOR_STATE;
}

void lcd_printByteAsHex(char c)
{
	lcd_print("0x");
	lcd_printNybbleAsHex(c >> 4);
	lcd_printNybbleAsHex(c);
}

void lcd_printNybbleAsHex(char c)
{

	// Make sure its only a nybble
	c &= 0x0F;

	if (c >= 0x0A)
	{			   // If its supposed to be a letter
		c += 0x07; // Offset of the number 10 to the letter A
	}

	c += 0x30; // Base value of the first number (0
	lcd_printchar(c);
}

void lcd_setbacklight(bool on)
{
	if (on)
	{
		PORTA |= LCD_BACKLIGHT;
	}
	else
	{
		PORTA &= 0xFF ^ LCD_BACKLIGHT;
	}
}