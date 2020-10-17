/*
 * TrafficLight.c
 *
 * Created: 2019-09-11 오후 5:28:50
 *  Author: Anthony Jo
 */ 

#include "TrafficLight.h"
#include "button.h"

volatile uint8_t state = VRHG;
volatile uint16_t TrafficCount = 0;

void TrafficLightCounter(void)
{
	TrafficCount++;
	TCNT0=5;
}
void TrafficLight_Init()
{
	TRAFFIC_LIGHT_DDR |= (1<<VERTICAL_RED) | (1<<VERTICAL_YELLOW) | (1<<VERTICAL_GREEN) 
	| (1<<HORIZONTAL_RED) | (1<<HORIZONTAL_YELLOW) | (1<<HORIZONTAL_GREEN);
}
void SetTrafficLight(uint8_t setLED)
{
	TRAFFIC_LIGHT_PORT &= ~( (1<<VERTICAL_RED) | (1<<VERTICAL_YELLOW) | (1<<VERTICAL_GREEN) 
	| (1<<HORIZONTAL_RED) | (1<<HORIZONTAL_YELLOW) | (1<<HORIZONTAL_GREEN));
	TRAFFIC_LIGHT_PORT |= setLED;
}
void Next_AutoState(uint8_t next_state, uint16_t delay_time)
{//change the next states after the delay 
	static uint16_t pretime;
	static uint8_t flag = 0;
	
	if(flag == 0)
	{
		flag = 1;
		pretime = TrafficCount;
		return;
	}
	if((TrafficCount - pretime) >= delay_time)
	{
		TrafficCount = 0;
		flag = 0;
		state = next_state;
	}
}
void Next_ManualState(uint8_t next_state)
{//change the next states when pressed button_1
	if(GetStateButton()==1)
	{
		state = next_state;
	}
}
void Auto_mode()
{
	switch(state)
	{
		case VRHG:
		SetTrafficLight( (1<<VERTICAL_RED) | (1<<HORIZONTAL_GREEN));
		Next_AutoState(VRHY, 5000);
		break;
		
		case VRHY:
		SetTrafficLight( (1<<VERTICAL_RED) | (1<<HORIZONTAL_YELLOW));
		Next_AutoState(VGHR, 2000);
		break;
		
		case VGHR:
		SetTrafficLight( (1<<VERTICAL_GREEN) | (1<<HORIZONTAL_RED));
		Next_AutoState(VYHR, 5000);
		break;
		
		case VYHR:
		SetTrafficLight( (1<<VERTICAL_YELLOW) | (1<<HORIZONTAL_RED));
		Next_AutoState(VRHG, 2000);
		break;
	}
}
void Manual_mode()
{
	switch(state)
	{
		case VRHG:
		SetTrafficLight( (1<<VERTICAL_RED) | (1<<HORIZONTAL_GREEN));
		Next_ManualState(VRHY);
		break;
		
		case VRHY:
		SetTrafficLight( (1<<VERTICAL_RED) | (1<<HORIZONTAL_YELLOW));
		Next_ManualState(VGHR);
		break;
		
		case VGHR:
		SetTrafficLight( (1<<VERTICAL_GREEN) | (1<<HORIZONTAL_RED));
		Next_ManualState(VYHR);
		break;
		
		case VYHR:
		SetTrafficLight( (1<<VERTICAL_YELLOW) | (1<<HORIZONTAL_RED));
		Next_ManualState(VRHG);
		break;
	}
}
void getColor(char *arrybuff)
{//output the status of the traffic light as a string
	switch(state) 
	{
		case VRHG:
		sprintf(arrybuff, "Vert: R, Hori: G");
		break;
		
		case VRHY:
		sprintf(arrybuff, "Vert: R, Hori: Y");
		break;
		
		case VGHR:
		sprintf(arrybuff, "Vert: G, Hori: R");
		break;
		
		case VYHR:
		sprintf(arrybuff, "Vert: Y, Hori: R");
		break;
	}
}