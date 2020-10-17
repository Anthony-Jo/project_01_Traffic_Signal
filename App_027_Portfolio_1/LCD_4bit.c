/*
 * LCD_4bit.c
 *
 * Created: 2019-09-11 오후 3:19:45
 *  Author: Anthony Jo
 */ 

#include "LCD_4bit.h"

void LCD_pulse_enable()
{
	LCD_ENABLE_PORT |= (1<<LCD_ENABLE); //Enable high
	_delay_ms(1); //delay between data
	LCD_ENABLE_PORT &= ~(1<<LCD_ENABLE); //Enable return to low
	_delay_ms(1);
}
void LCD_clear()
{
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}
void LCD_Init()
{
	LCD_DATA_DDR = 0xff;
	LCD_RS_DDR |= (1<<LCD_RS);
	LCD_ENABLE_DDR |= (1<<LCD_ENABLE);
	
	_delay_ms(20);	//requires more 15ms on hardware
	LCD_WriteCommandInit(0x30);
	_delay_ms(5);	//requires more 4ms on hardware
	LCD_WriteCommandInit(0x30);
	_delay_ms(200); //requires more 100ms on hardware
	LCD_WriteCommandInit(0x30);
	LCD_WriteCommandInit(COMMAND_4_BIT_MODE);
	LCD_WriteCommand(COMMAND_4_BIT_MODE);			
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY);
	LCD_WriteCommand(COMMAND_ENTRY_MODE);	
	LCD_WriteCommand(COMMAND_DISPLAY_ON);
}
void LCD_write_string(char *string)
{
	for(uint8_t i=0; i<string[i]; i++) //until access on a null value
	{
		LCD_WriteData(string[i]); //output string units
	}
}
void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;	 //[0 15]
	row %= 2;	// [0  1]
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	LCD_WriteCommand(command); //move cursor
}
void LCD_WriteCommand(uint8_t cmdData)
{
	LCD_RS_PORT &= ~(1<<LCD_RS);  //RS low
	LCD_DATA_PORT = (LCD_RS_PORT & 0x0f) | (cmdData & 0xf0); //cmdData output upper 4bits
	LCD_pulse_enable();
	LCD_DATA_PORT = (LCD_RS_PORT & 0x0f) | ( (cmdData & 0x0f)<<4 ); //4bit shift, and output lower 4bits
	LCD_pulse_enable();
}
void LCD_WriteCommandInit(uint8_t cmdData)
{
	LCD_RS_PORT &= ~(1<<LCD_RS);  //RS low
	LCD_DATA_PORT = (LCD_RS_PORT & 0x0f) | (cmdData & 0xf0); //cmdData output upper 4bit
	LCD_pulse_enable();
}
void LCD_WriteData(uint8_t data)
{
	LCD_RS_PORT |= (1<<LCD_RS);  //RS high
	LCD_DATA_PORT = (LCD_RS_PORT & 0x0f) | (data & 0xf0); //data output output upper 4bits
	LCD_pulse_enable();
	LCD_DATA_PORT = (LCD_RS_PORT & 0x0f) | ( (data & 0x0f)<<4 ); //shift, and output lower 4bits
	LCD_pulse_enable();
}
