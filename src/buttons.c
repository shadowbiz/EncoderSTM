#include "buttons.h"

#define MASK_BUTTONS 	        (1<<ENTER)


unsigned int comp = 0;
unsigned char pressedKey = 0,Key = 0;;
unsigned char c1 = 0,c2 = 0;

//_______________________________________
void BUT_Init(void)
{
  DDRX_BUTTON &= ~(MASK_BUTTONS); 
  PORT_BUTTON |= MASK_BUTTONS;
  SetBit(PORT_BUTTON,ENTER);
}

void BUT_Debrief(void)
{
unsigned char key = 0;


  //последовательный опрос выводов мк
  
  if(BitIsClear(PIN_BUTTON, ENTER))        
    key = KEY_ENTER; 
  else
   key = KEY_NULL;
  

 if (key)                                     //если в переменной что то есть
  {
   if (comp == THRESHOLD4)                  // очень очень длительное нажатие кнопки
      {comp = THRESHOLD4-5; 
       return;}
   
   if (comp == THRESHOLD3)                  // очень длительное нажатие кнопки
     {comp = THRESHOLD3-15; 
     if(++c2 == 2){
     comp = THRESHOLD4;
     c2 = 0;
     }
       ES_PlaceEvent(EVENT_KEY_ENTER_VERY_LONG );        //тащим кнопку нажатую
       return;
     } 
   if (comp == THRESHOLD2)                // длительное нажатие           
    {
      comp = THRESHOLD2+1;
      ES_PlaceEvent(EVENT_KEY_ENTER_LONG );                     //тащим кнопку нажатую
      return;
    }
  else if (comp < THRESHOLD4)               //если меньше задержки на длительное нажатие
    comp++;                                 // inc счетчик
    if (comp == THRESHOLD)                  //фиксируем одинарное нажатие
    { comp = THRESHOLD+10;                  //изменяем значение счетчика чтобы не считал неколько раз нажатие  
      pressedKey = KEY_ENTER_1;             //тащим кнопку нажатую в буфер
      return;
    }
    
  if(comp >= THRESHOLD2) pressedKey = 0;                       //чтобы не сработала ENTER отпредыдущего раза
    
  }
 else 
    comp=0;
 
  if(pressedKey == KEY_ENTER_1 && BitIsSet(PIN_BUTTON, ENTER)) //кли отпустили кнопку, и есть в буфере она,то фиксируем
   { ES_PlaceEvent(EVENT_KEY_ENTER);
     pressedKey = 0;
   }
 
}
void BUT_GetKey(void)
{
  Key = pressedKey;
  pressedKey = 0;
   
  if (Key == KEY_ENTER) ES_PlaceEvent(EVENT_KEY_ENTER  );
  if (Key == KEY_ENTER_LONG) ES_PlaceEvent(EVENT_KEY_ENTER_LONG );
  if (Key == KEY_ENTER_VERY_LONG) ES_PlaceEvent(EVENT_KEY_ENTER_VERY_LONG );
}