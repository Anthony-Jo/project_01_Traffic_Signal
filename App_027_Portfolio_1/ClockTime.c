/*
 * ClockTime.c
 *
 * Created: 2019-09-10 오후 06:04:54
 *  Author: Anthony Jo
 */ 
#include "ClockTime.h"

volatile uint8_t sec=0, minu=0, hour=0; 
volatile uint16_t timeCount_system=0;

void ClockTimeCount() //count time as interrupt
{
	timeCount_system++; 
	if (timeCount_system >= 1000)
	{
		timeCount_system = 0;
		sec++;
		if (sec >= 60)
		{
			sec = 0;
			minu++;
		}
		if (minu >= 60)
		{
			minu = 0;
			hour++;
		}
		if (hour >= 24)
		{
			hour = 0;
		}
	}
	TCNT0=5;
}
uint8_t GetHour()  //return hours as a constant
{
	return hour;
}
uint8_t GetMinu() //return minutes as a constant
{
	return minu;
}
uint8_t GetSec() //return seconds as constant
{
	return sec;
}

