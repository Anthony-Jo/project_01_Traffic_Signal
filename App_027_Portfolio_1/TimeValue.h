/*
 * TimeValue.h
 *
 * Created: 2019-09-16 오후 7:57:52
 *  Author: kccistc
 */ 


#ifndef TIMEVLAUE_H_
#define TIMEVLAUE_H_

#include "LIB.h"

typedef struct time{
	uint8_t time;
	uint8_t minute;
	uint8_t second;
}TIME;

uint8_t Delay(uint32_t delay);
void Timer0Init();
void Timer0_OVF_Interrupt_Callback();
void getTime(TIME *pTime);
uint64_t GetSystick();

#endif /* TIMEVLAUE_H_ */