#include "event-system.h"

//кольцевой буфер
unsigned char cycleBuf[SIZE_BUF];
static volatile unsigned char tailBuf = 0;
unsigned char headBuf = 0;
static volatile unsigned char countBuf = 0;

//взять событие
unsigned char ES_GetEvent(void)
{
  unsigned char event;
  if (countBuf > 0){                    //если приемный буфер не пустой  
    event = cycleBuf[headBuf];          //считать из него событие    
    countBuf--;                         //уменьшить счетчик 
    headBuf++;                          //инкрементировать индекс головы буфера  
    if (headBuf == SIZE_BUF) headBuf = 0;
    return event;                         //вернуть событие
  }
  return 0;
}

//положить событие
void ES_PlaceEvent(unsigned char event) 
{
  if (countBuf < SIZE_BUF){                    //если в буфере еще есть место                     
      cycleBuf[tailBuf] = event;               //кинуть событие в буфер
      tailBuf++;                               //увеличить индекс хвоста буфера 
      if (tailBuf == SIZE_BUF) tailBuf = 0;  
      countBuf++;                              //увеличить счетчик 
  }
} 

//*****************************************************************************

volatile unsigned char currentState = 0;

const struct ROW_TABLE
{
    unsigned char state;           //состояние
    unsigned char event;           //событие
    unsigned char nextState;       //следующее состояние
    void (*pStateFunc)(void);                       
};

void ES_Init(void)
{
  tailBuf = 0;
  headBuf = 0;
  countBuf = 0;
  currentState = STATE_VOLUME;
}
void EmptyFunc(void)
{
}
//таблица состояний
const struct ROW_TABLE table[] = {  
//   STATE              EVENT                 NEXT STATE             STATE_FUNC     

{STATE_VOLUME,      EVENT_0_5s_TIMER,        STATE_NO_CHANGE,    Change_Disp     },      //каждые пол секунды меняемна дисп. время
{STATE_VOLUME,      EVENT_ADC,               STATE_NO_CHANGE,    GUI_Adc                     },      //каждые пол секунды меняемна дисп. время
{STATE_VOLUME,      EVENT_KEY_ENTER,         STATE_NO_CHANGE,    GUI_Button                     },      //каждые пол секунды меняемна дисп. время

 //обязательная пустая строка таблицы 
    {0,                  0,                    0,                        NULL           }
};
void ES_Dispatch(unsigned char currentEvent)
{
    unsigned char i;
        
    for (i=0; table[i].state; i++){
        if (table[i].state == currentState && table[i].event == currentEvent){
          if (table[i].nextState != STATE_NO_CHANGE){
              currentState = table[i].nextState;
          }
          table[i].pStateFunc();
          break;
        }
    }
}
void ChangeStatus(unsigned char data) {
  LCD_Clear();
  currentState = data;
  }