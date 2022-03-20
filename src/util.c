#include "util.h"

void delay(int ms)
{
    // This is a very simple delay loop.
    int delay = ms * 333;
    int i = 0;
    while ((i++) < delay)
        ;
}