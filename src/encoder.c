#include "encoder.h"




volatile unsigned char bufEnc = 0; //буфер энкодера

//функци€ инициализации
//__________________________________________
void ENC_InitEncoder(void)
{
 
  GPIO_Init(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);//вход вкл подт€гивающий резистор
  GPIO_Init(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_5, GPIO_MODE_IN_PU_NO_IT);
}

//функци€ опроса энкодера
//___________________________________________
void ENC_PollEncoder(void)
{
static unsigned char stateEnc; 	//хранит последовательность состо€ний энкодера
unsigned char tmp;  
unsigned char currentState = 0;

//провер€ем состо€ние выводов микроконтроллера

if(GPIO_ReadInputPin(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_4)) {SetBit(currentState,0);}
if(GPIO_ReadInputPin(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_5)) {SetBit(currentState,1);}
//if ((PIN_Enc & (1<<Pin1_Enc))!= 0) {SBR(currentState,0);}
//if ((PIN_Enc & (1<<Pin2_Enc))!= 0) {SBR(currentState,1);}

//если равно предыдущему, то выходим
tmp = stateEnc;
if (currentState == (tmp & b00000011)) return;

//если не равно, то сдвигаем и сохран€ем в озу
stateEnc = (tmp<<2)|currentState;

//сравниваем получившуюс€ последовательность
if (tmp == b11100001) bufEnc = LEFT_SPIN;
if (tmp == b11010010) bufEnc = RIGHT_SPIN;
return;
}

//функци€ возвращающа€ значение буфера энкодера
//_____________________________________________
unsigned char ENC_GetStateEncoder(void)
{
  unsigned char tmp = bufEnc;
  
  if (tmp)
  {
    bufEnc = 0;
    return tmp;
  }
  return 0;  
}


