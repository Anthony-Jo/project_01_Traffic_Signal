/*
 * LED.h
 *
 * Created: 2019-09-12 오후 3:42:15
 *  Author: Anthony Jo
 */ 


#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRA
#define LED_PORT PORTA

#define LED_AUTO	3
#define LED_MANUAL	5

void LED_Init();
void Auto_LED();
void Manual_LED();
#endif /* LED_H_ */