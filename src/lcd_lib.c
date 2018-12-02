#include "lcd_lib.h"


void LCD_WriteComInit(unsigned char data)
{
  Delay_us(40);
  //GPIO_WriteLow(PORT_SIG,RS);
  ClearBit(PORT_SIG, RS);	//��������� RS � 0 - �������
#ifdef BUS_4BIT
  unsigned char tmp; 
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);
  PORT_DATA = tmp;		//����� ������� ������� 
#else
  PORT_DATA = data;		//����� ������ �� ���� ���������� 
#endif  
  SetBit(PORT_SIG, EN);	        //��������� E � 1
  Delay_us(5);
  ClearBit(PORT_SIG, EN);	//��������� E � 0 - ������������ �����
}


//����� �������
#pragma inline = forced
void LCD_CommonFunc(unsigned char data)
{
#ifdef BUS_4BIT  
  unsigned char tmp; 
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);

  PORT_DATA = tmp;		//����� ������� ������� 
  SetBit(PORT_SIG, EN);	        
  Delay_us(5);
  ClearBit(PORT_SIG, EN);	

  data = swap_nibbles(data);
  tmp  = PORT_DATA & 0x0f;
  tmp |= (data & 0xf0);
 
  PORT_DATA = tmp;		//����� ������� ������� 
  SetBit(PORT_SIG, EN);	        
  Delay_us(5);
  ClearBit(PORT_SIG, EN);	 
#else 
  PORT_DATA = data;		//����� ������ �� ���� ���������� 
  SetBit(PORT_SIG, EN);	        //��������� E � 1
  Delay_us(5);
  ClearBit(PORT_SIG, EN);	//��������� E � 0 - ������������ �����
#endif
}

//������� �������� ���������� lcd
#pragma inline = forced
void LCD_Wait(void)
{
#ifdef CHECK_FLAG_BF
  #ifdef BUS_4BIT
  
  unsigned char data;
  DDRX_DATA &= 0x0f;            //������������� ���� �� ����
  PORT_DATA |= 0xf0;	        //�������� pull-up ���������
  SetBit(PORT_SIG, RW);         //RW � 1 ������ �� lcd
  ClearBit(PORT_SIG, RS);	//RS � 0 �������
  do{
    SetBit(PORT_SIG, EN);	
    Delay_us(5);
    data = PIN_DATA & 0xf0;      //������ ������ � �����
    ClearBit(PORT_SIG, EN);
    data = __swap_nibbles(data);
    SetBit(PORT_SIG, EN);	
    Delay_us(5);
    data |= PIN_DATA & 0xf0;      //������ ������ � �����
    ClearBit(PORT_SIG, EN);
    data = swap_nibbles(data);
  }while((data & (1<<FLAG_BF))!= 0 );
  ClearBit(PORT_SIG, RW);
  DDRX_DATA |= 0xf0; 
  
  #else
  unsigned char data;
  DDRX_DATA = 0;                //������������� ���� �� ����
  PORT_DATA = 0xff;	        //�������� pull-up ���������
  SetBit(PORT_SIG, RW);         //RW � 1 ������ �� lcd
  ClearBit(PORT_SIG, RS);	//RS � 0 �������
  do{
    SetBit(PORT_SIG, EN);	
    Delay_us(5);
    data = PIN_DATA;            //������ ������ � �����
    ClearBit(PORT_SIG, EN);	
  }while((data & (1<<FLAG_BF))!= 0 );
  ClearBit(PORT_SIG, RW);
  DDRX_DATA = 0xff; 
  #endif    
#else
  Delay_us(40);
#endif  
}

//������� ������ ������� 
void LCD_WriteCom(unsigned char data)
{
  LCD_Wait();
  ClearBit(PORT_SIG, RS);	//��������� RS � 0 - �������
  LCD_CommonFunc(data);
}

//������� ������ ������
void LCD_WriteData(unsigned char data)
{
  LCD_Wait();
  SetBit(PORT_SIG, RS);	        //��������� RS � 1 - ������
  LCD_CommonFunc(data);
}

//������� �������������
void LCD_Init(void)
{
#ifdef BUS_4BIT
  DDRX_DATA |= 0xf0;
  PORT_DATA |= 0xf0; 
#else  
  DDRX_DATA |= 0xff;
  PORT_DATA |= 0xff;
#endif
  
  DDRX_SIG |= (1<<RS)|(1<<EN);
  PORT_SIG |= (1<<RS)|(1<<EN);
  PORT_SIG_CR1 |= (1<<RS)|(1<<EN);
 // ClearBit(PORT_SIG, RW);
  Delay_ms(40);
  
#ifdef HD44780  
  LCD_WriteComInit(0x30); 
  Delay_ms(10);
  LCD_WriteComInit(0x30);
  Delay_ms(1);
  LCD_WriteComInit(0x30);
#endif
  
#ifdef BUS_4BIT  
  LCD_WriteComInit(0x20); //4-�� ��������� ����
  LCD_WriteCom(0x28); //4-�� ��������� ����, 2 - ������
#else
  LCD_WriteCom(0x38); //8-�� ��������� ����, 2 - ������
#endif
  LCD_WriteCom(0x08);
  LCD_WriteCom(0x0c);  //0b00001111 - ������� ���, ������ � �������� ���������
  LCD_WriteCom(0x01);  //0b00000001 - ������� �������
  Delay_ms(2);
  LCD_WriteCom(0x06);  //0b00000110 - ������ �������� ������, ������ ���
}

//������� ������ ������ �� ���� ������
void LCD_SendStringFlash(const char *str)
{
  unsigned char data;			
  while (*str)
  {
    data = *str++;
    LCD_WriteData(data);
  }
}

//������� ����� ������ �� ���
void LCD_SendString(char *str)
{
  unsigned char data;
  while (*str)
  {
    data = *str++;
    LCD_WriteData(data);
  }
}

void LCD_Clear(void)
{
  LCD_WriteCom(0x01);
  Delay_ms(2);
}