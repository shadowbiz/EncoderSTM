#ifndef LCD_LIB_H
#define LCD_LIB_H

#include <intrinsics.h>
#include "iostm8s003f3.h"

//порт к которому подключена шина данных ЖКД
#define PORT_DATA PC_ODR
#define PIN_DATA  PC_IDR
#define DDRX_DATA PC_DDR

//порт к которому подк|ючены управляющие выводы ЖКД
#define PORT_SIG PA_ODR
#define PIN_SIG  PA_IDR
#define DDRX_SIG PA_DDR
#define PORT_SIG_CR1 PA_CR1

//Номера выводов к которым подключены управляющие выводы ЖКД 
#define EN 1
#define RS 2


#define F_CPU 8000000

//макросы для работы с битами
#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
#define SetBit(reg, bit)         reg |= (1<<(bit))	
#define FLAG_BF 7

#define swap_nibbles(reg)       reg = (((reg&0x0f)<<4) | ((reg&0xf0)>>4))

//#define CHECK_FLAG_BF
#define BUS_4BIT
#define HD44780


/*позиционирование курсора*/
#define LCD_Goto(x,y) LCD_WriteCom(((((y)& 1)*0x40)+((x)& 15))|128) 

//прототипы функций
void LCD_Init(void);//инициализация портов и жкд
void LCD_Clear(void);//очистка жкд
void LCD_WriteData(unsigned char data); //выводит байт данных на жкд
void LCD_WriteCom(unsigned char data); //посылает команду жкд
void LCD_SendStringFlash(const char *str); //выводит строку из флэш памяти
void LCD_SendString(char *str); //выводит строку из ОЗУ
#endif