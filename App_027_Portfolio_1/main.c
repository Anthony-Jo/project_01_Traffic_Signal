/*
* App_027_Portfolio_1.c
*
* Created: 2019-09-11 15:12:26
* Author : Anthony Jo
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "Button.h"
#include "ClockTime.h"
#include "LCD_4bit.h"
#include "LED.h"
#include "TrafficLight.h"

uint8_t trafficMode = AUTO; //traffic light mode's default
char buff[20] = {0}; //string for LCD output

ISR(TIMER0_OVF_vect)
{
	ClockTimeCount(); //time counter for time clock
	TrafficLightCounter(); //time counter for traffic light
}
void TimerClock_Init()
{
	TCCR0 |= (1<<CS02) | (0<<CS01) | (0<<CS00); //set the 64 division
	TIMSK |= (1<<TOIE0);
	TCNT0=5; //1 ms count
}
void Mode_Change(uint8_t FromChangeMode, uint8_t ToChangeMode) // function for mode change
{
	if( GetModeButton() && (trafficMode == FromChangeMode) )
	{
		trafficMode = ToChangeMode;
	}
}
int main(void)
{
	Button_Init();
	LCD_Init();
	LED_Init();
	TimerClock_Init();
	TrafficLight_Init();

	sei();
	
	while (1)
	{
		sprintf(buff, "Time: %02d:%02d:%02d ",GetHour(),GetMinu(),GetSec()); //current time output on LCD
		LCD_goto_XY(0,0); //at the first line
		LCD_write_string(buff);
		
		if(trafficMode == AUTO)
		{	
			getColor(buff); //traffic light state output on LCD
			LCD_goto_XY(1,0); //at the second line
			LCD_write_string(buff);
			Auto_mode(); 
			Auto_LED(); 
			Mode_Change(AUTO,MANUAL); 
		}
		else if (trafficMode == MANUAL)
		{
			getColor(buff); //traffic light state output on LCD
			LCD_goto_XY(1,0); //at the second line
			LCD_write_string(buff);
			Manual_mode();
			Manual_LED();
			Mode_Change(MANUAL,AUTO);
		}
	}
}

