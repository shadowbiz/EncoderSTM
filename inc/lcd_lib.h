#ifndef LCD_LIB_H
#define LCD_LIB_H

#include <intrinsics.h>
#include "iostm8s003f3.h"

//���� � �������� ���������� ���� ������ ���
#define PORT_DATA PC_ODR
#define PIN_DATA  PC_IDR
#define DDRX_DATA PC_DDR

//���� � �������� ����|����� ����������� ������ ���
#define PORT_SIG PA_ODR
#define PIN_SIG  PA_IDR
#define DDRX_SIG PA_DDR
#define PORT_SIG_CR1 PA_CR1

//������ ������� � ������� ���������� ����������� ������ ��� 
#define EN 1
#define RS 2


#define F_CPU 8000000

//������� ��� ������ � ������
#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
#define SetBit(reg, bit)         reg |= (1<<(bit))	
#define FLAG_BF 7

#define swap_nibbles(reg)       reg = (((reg&0x0f)<<4) | ((reg&0xf0)>>4))

//#define CHECK_FLAG_BF
#define BUS_4BIT
#define HD44780


/*���������������� �������*/
#define LCD_Goto(x,y) LCD_WriteCom(((((y)& 1)*0x40)+((x)& 15))|128) 

//��������� �������
void LCD_Init(void);//������������� ������ � ���
void LCD_Clear(void);//������� ���
void LCD_WriteData(unsigned char data); //������� ���� ������ �� ���
void LCD_WriteCom(unsigned char data); //�������� ������� ���
void LCD_SendStringFlash(const char *str); //������� ������ �� ���� ������
void LCD_SendString(char *str); //������� ������ �� ���
#endif