/*
 * TrafficLight.h
 *
 * Created: 2019-09-11 오후 5:29:04
 *  Author: Anthony Jo
 */ 


#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>

#define TRAFFIC_LIGHT_DDR	DDRC
#define TRAFFIC_LIGHT_PORT	PORTC

#define AUTO	0
#define MANUAL	1

#define VERTICAL_GREEN		0
#define VERTICAL_YELLOW		1
#define VERTICAL_RED		2
#define HORIZONTAL_RED		3
#define HORIZONTAL_YELLOW	4
#define HORIZONTAL_GREEN	5

#define VRHG 0
#define VRHY 1
#define VGHR 2
#define VYHR 3

void TrafficLightCounter();
void TrafficLight_Init();
void SetTrafficLight(uint8_t setLED);
void Next_AutoState(uint8_t next_state, uint16_t delay_time);
void Next_ManualState(uint8_t next_state);
void Auto_mode();
void Manual_mode();
void getColor();
#endif /* TRAFFICLIGHT_H_ */