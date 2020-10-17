/*
 * LCD_4bit.h
 *
 * Created: 2019-09-11 오후 3:20:01
 *  Author: Anthony Jo
 */ 


#ifndef LCD_4BIT_H_
#define LCD_4BIT_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LCD_DATA_DDR		DDRD
#define LCD_DATA_PORT		PORTD
#define LCD_RS_DDR			DDRD
#define LCD_RS_PORT			PORTD
#define LCD_ENABLE_DDR		DDRD
#define LCD_ENABLE_PORT		PORTD
#define LCD_RS				0
#define LCD_ENABLE			1

#define COMMAND_CLEAR_DISPLAY		0x01
#define COMMAND_4_BIT_MODE			0x28
#define COMMAND_8_BIT_MODE			0x38 //0x3 뒤에 상관없음
#define COMMAND_DISPLAY_ON			0x0c
#define COMMAND_DISPLAY_OFF			0x08
#define COMMAND_ENTRY_MODE			0x06

void LCD_pulse_enable();
void LCD_clear();
void LCD_Init();
void LCD_write_string(char *string);
void LCD_goto_XY(uint8_t row, uint8_t col);
void LCD_WriteCommand(uint8_t cmdData);
void LCD_WriteCommandInit(uint8_t cmdData);
void LCD_WriteData(uint8_t data);


#endif /* LCD_4BIT_H_ */