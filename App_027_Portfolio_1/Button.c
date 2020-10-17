/*
 * Button.c
 *
 * Created: 2019-09-12 오전 10:34:03
 * Author : Anthony Jo
*/

#include "Button.h"

void Button_Init()
{
	BUTTON_MODE_DDR &= ~(1<<BUTTON_MODE);
	BUTTON_STATE_DDR &= ~(1<<BUTTON_STATE);
}
uint8_t GetModeButton() //if push the button_0
{
	static uint8_t prevModeButtonState = 1; 
	return GetButton(BUTTON_MODE, &prevModeButtonState); //changed at low edge
}
uint8_t GetStateButton() //if push the button_1
{
	static uint8_t prevSignalButtonState = 1;
	return GetButton(BUTTON_STATE, &prevSignalButtonState); //changed at low edge
}
uint8_t GetButton(uint8_t button, uint8_t *prevButtonState)
{
	uint8_t curButtonState = 1;
	
	curButtonState = (PINA & (1<<button)) >> button;
	if ( (curButtonState == 0) && (*prevButtonState == 1) ) //if button has kept pressed, isn't work
	{
		*prevButtonState = curButtonState;
		return 0;
	}
	else if ( (curButtonState == 1) && (*prevButtonState == 0) ) //if button has kept pressed, isn't work
	{
		*prevButtonState = curButtonState;
		return 1;
	}
	return 0;
}

