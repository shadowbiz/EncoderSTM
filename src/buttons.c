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


  //���������������� ����� ������� ��
  
  if(BitIsClear(PIN_BUTTON, ENTER))        
    key = KEY_ENTER; 
  else
   key = KEY_NULL;
  

 if (key)                                     //���� � ���������� ��� �� ����
  {
   if (comp == THRESHOLD4)                  // ����� ����� ���������� ������� ������
      {comp = THRESHOLD4-5; 
       return;}
   
   if (comp == THRESHOLD3)                  // ����� ���������� ������� ������
     {comp = THRESHOLD3-15; 
     if(++c2 == 2){
     comp = THRESHOLD4;
     c2 = 0;
     }
       ES_PlaceEvent(EVENT_KEY_ENTER_VERY_LONG );        //����� ������ �������
       return;
     } 
   if (comp == THRESHOLD2)                // ���������� �������           
    {
      comp = THRESHOLD2+1;
      ES_PlaceEvent(EVENT_KEY_ENTER_LONG );                     //����� ������ �������
      return;
    }
  else if (comp < THRESHOLD4)               //���� ������ �������� �� ���������� �������
    comp++;                                 // inc �������
    if (comp == THRESHOLD)                  //��������� ��������� �������
    { comp = THRESHOLD+10;                  //�������� �������� �������� ����� �� ������ �������� ��� �������  
      pressedKey = KEY_ENTER_1;             //����� ������ ������� � �����
      return;
    }
    
  if(comp >= THRESHOLD2) pressedKey = 0;                       //����� �� ��������� ENTER ������������� ����
    
  }
 else 
    comp=0;
 
  if(pressedKey == KEY_ENTER_1 && BitIsSet(PIN_BUTTON, ENTER)) //��� ��������� ������, � ���� � ������ ���,�� ���������
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