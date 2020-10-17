/*
 * Button.h
 *
 * Created: 2019-09-12 오전 10:35:11
 *  Author: Anthony Jo
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU	16000000UL
#include <avr/io.h>

#define BUTTON_MODE_DDR		DDRA
#define BUTTON_MODE_PIN		PINA
#define BUTTON_STATE_DDR	DDRA
#define BUTTON_STATE_PIN	PINA
#define BUTTON_MODE			0			
#define BUTTON_STATE		1 

void Button_Init();
uint8_t GetModeButton();
uint8_t GetStateButton();
uint8_t GetButton(uint8_t button, uint8_t *prevButtonState);


#endif /* BUTTON_H_ */