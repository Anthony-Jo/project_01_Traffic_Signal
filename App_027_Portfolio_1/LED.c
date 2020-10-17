/*
 * LED.c
 *
 * Created: 2019-09-12 오후 3:42:03
 *  Author: Anthony Jo
 */ 
#include "LED.h"

void LED_Init()
{
	LED_DDR |= (1<<LED_AUTO) | (1<<LED_MANUAL);
}
void Auto_LED() //turn on the LED, at auto mode
{
	LED_PORT = 0x08;
}
void Manual_LED() //turn on the LED, at manual mode
{
	LED_PORT = 0x20;
}