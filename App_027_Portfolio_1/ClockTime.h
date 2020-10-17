/*
 * ClockTime.h
 *
 * Created: 2019-09-07 오전 11:06:09
 *  Author: Anthony Jo
 */ 


#ifndef CLOCK_TIME_H_
#define CLOCK_TIME_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void ClockTimeCount();
uint8_t GetHour();
uint8_t GetMinu();
uint8_t GetSec();

#endif /* CLOCK_TIME_H_ */