#include "interface.h" 
#include "lcd_lib.h"
#include "event-system.h"
#include "math.h"


extern unsigned int faza;
extern unsigned int buf;
unsigned int current_zad = 15,volt_zad = 138;         //100 - 1ампер, 2000 20 А
unsigned int count = 0;
//unsigned int current = 0;
unsigned int buf_curr = 0,buf_v;
unsigned char dig[4] = 0;

extern unsigned char count_adc,flags,c = 50,count_enter = 0;
extern unsigned int buf_adc[100],buf_adc_v;
unsigned long Vskt = 0,volt = 0;
long double V = 0,current = 0;



void Init_Chars(void){
   
  LCD_WriteCom(0x60); //рисуем значка молнии
  LCD_WriteData(0x01);  // данные
  LCD_WriteData(0x02);
  LCD_WriteData(0x04);
  LCD_WriteData(0x08);
  LCD_WriteData(0x1f);
  LCD_WriteData(0x02);
  LCD_WriteData(0x04);
  LCD_WriteData(0x08);
  
}
//+-------------------------------------------------------------------------------------+
//| Функция                        |
//+-------------------------------------------------------------------------------------+
void Change_Disp(void){
  
unsigned char tmp;      //переменная для расчетов
      
     LCD_Goto(0,0);
     dig[0] = (unsigned int)current%10;     //остача от деления на 10
     dig[1] = (unsigned int)current/10;    //сколько целых 10 в числе
     dig[2] = dig[1]%10;                  //разбиваем на рязряды остальные 2 разряда
     dig[3] = dig[1]/10;
     BCD_1Lcd(dig[3]);                                      //выводим напругу на дисплей(преобр. 3-раздядного числа по разрядам)
     BCD_1Lcd(dig[2]);  
     LCD_WriteData('.');
     BCD_1Lcd(dig[0]);
     LCD_WriteData(' ');
     LCD_SendString("A");
        
     LCD_Goto(0,1);
     dig[0] = (unsigned int)volt%10;     //остача от деления на 10
     dig[1] = (unsigned int)volt/10;    //сколько целых 10 в числе
     dig[2] = dig[1]%10;                  //разбиваем на рязряды остальные 2 разряда
     dig[3] = dig[1]/10;
     BCD_1Lcd(dig[3]);                                      //выводим напругу на дисплей(преобр. 3-раздядного числа по разрядам)
     BCD_1Lcd(dig[2]);  
     LCD_WriteData('.');
     BCD_1Lcd(dig[0]);
     LCD_WriteData(' ');
     LCD_SendString("V");
     
     LCD_Goto(9,0);
       if(count_enter == 1)
       LCD_WriteData('>');
      else
        LCD_WriteData(' ');
     dig[0] = current_zad%10;                                  //остача от деления на 10
     dig[1] = current_zad/10;                                  //сколько целых 10 в числе
     dig[2] = dig[1]%10;                                   //разбиваем на рязряды остальные 2 разряда
     dig[3] = dig[1]/10;
     BCD_1Lcd(dig[3]);                                      //выводим напругу на дисплей(преобр. 3-раздядного числа по разрядам)
     BCD_1Lcd(dig[2]);  
     LCD_WriteData('.');
     BCD_1Lcd(dig[0]);
     LCD_WriteData(' ');
     LCD_SendString("A");
     
     LCD_Goto(9,1);
      if(count_enter == 2)
       LCD_WriteData('>');
      else
        LCD_WriteData(' ');
     dig[0] = (unsigned int)volt_zad%10;     //остача от деления на 10
     dig[1] = (unsigned int)volt_zad/10;    //сколько целых 10 в числе
     dig[2] = dig[1]%10;                  //разбиваем на рязряды остальные 2 разряда
     dig[3] = dig[1]/10;
     BCD_1Lcd(dig[3]);                                      //выводим напругу на дисплей(преобр. 3-раздядного числа по разрядам)
     BCD_1Lcd(dig[2]);  
     LCD_WriteData('.');
     BCD_1Lcd(dig[0]);
     LCD_WriteData(' ');
     LCD_SendString("V");
    
    
     
       if(BitIsClear(flags,REG_U_I))
  {  
    if(BitIsClear(flags,F2))
    {
      LCD_Goto(7,0);
      LCD_SendString("F1");
      }
    else
      {
      LCD_Goto(7,0);
      LCD_SendString("F2");
      }
    LCD_Goto(7,1);
    LCD_WriteData('I');
    }
  else
      { 
    LCD_Goto(7,0);
    LCD_SendString("  ");
    LCD_Goto(7,1);
    LCD_WriteData('U');
    }
    
    if(BitIsClear(flags,STATE_ENABLE))
  {  
    LCD_Goto(8,1);
    LCD_WriteData(' ');
    }
  else
      {  
    LCD_Goto(8,1);
    LCD_WriteData(0x04);      //вывод значка молнии
    }
   
     if(count_enter == 3)
  {LCD_Goto(7, 1);
  LCD_WriteCom(0x0d);     //вкулючаем курсор
  }
  else if(count_enter == 4)
  {
  LCD_Goto(8, 1);
  LCD_WriteCom(0x0d);     //вкулючаем курсор
         }
  else 
  {
  LCD_Goto(8, 1);
  LCD_WriteCom(0x0c);        //выключаем курсор
         }
      
   }

void GUI_Adc(void)
{
  if(BitIsClear(ADC1->CSR,0))   //если 6 канал АЦП
  {
   buf_v =  buf_v + buf_adc_v;
        if(++count == 8)
     {
       buf_v = buf_v>>3;
       volt =  (unsigned long)buf_v*157/1023;
       buf_v = 0;
       count = 0;
       ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_5,ADC1_ALIGN_RIGHT);
       
     if(volt >= volt_zad && BitIsSet(flags,REG_U_I))                  //достигли уровня ограничения напруги
     SetBit(flags,F2);             //поставили флаг
     else
       ClearBit(flags,F2);
          }
   }
 
 if(BitIsSet(ADC1->CSR,0))      //если меряли ток
  {
  
    buf_curr = buf_curr + V;    //сумируем в буфер ток
    if(++count == 2)
     {
      buf_curr = buf_curr/2;    //опредеояем среднее
      current = buf_curr/17;    //определяем ток
      buf_curr = 0;
      count = 0;
              
      ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_6,ADC1_ALIGN_RIGHT);        //меняем канал АЦП на напругу
      /*Start Conversion */
      ADC1_StartConversion();
      
      
      if(BitIsClear(flags,F2) || BitIsClear(flags,REG_U_I))             //если регулятор тока
      {
      if(current_zad > current && faza != 10)
      faza = faza--;
      if(current_zad < current && faza != 1000)
      faza = faza++;
      }
      if(BitIsSet(flags,REG_U_I) || BitIsSet(flags,F2))                                      //если регулятор напруги
       {
         if(BitIsSet(flags,STATE_ENABLE)){
      if(volt_zad >= volt)
        GPIO_WriteHigh(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_3);
      if(volt_zad < volt)
        GPIO_WriteLow(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_3);
         }
      }
      
       //GPIO_WriteReverse(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_4);
       }
    for(unsigned char i = 0; i<50; i++)
  {
  Vskt = Vskt+buf_adc[i];       //сума 50 выборок тока
  }
           
  V = (double)Vskt/50;         //среднее
  V = V*4960/1023;              //напруга
  Vskt = 0;
        
     }
//if(current >= 30)   
 //  SetBit(flags,ERROR_CURRENT);
      }

void GUI_Button(void){
  if(++count_enter == 5)
     count_enter = 0;
      }
