#include "types.h"
#include "hardware.h"
#include "lcd.h"
#include "sd.h"

int main()
{

	lcd_setbacklight(true);
	lcd_init();

	lcd_print("Hello There");

	return (0);
}
