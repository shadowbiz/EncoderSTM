#include "stm8s_conf.h"
#include "iostm8s003f3.h"
#include "lcd_lib.h"
#include "bits_macros.h"
#include "stm8s_tim4.h"
#include "timer.h"
#include "stm8s_exti.h"
#include "event-system.h"
#include "encoder.h"
#include "adc.h"


  

void Delay_ms(uint16_t nCount);
void Delay_us(uint16_t nCount);


unsigned int faza = 780;
extern unsigned char flags;
int SystemInit(void)
{
    return 0;
}

void main(void)
{
  unsigned char event = 0;
  
  LCD_Init();
  TIM4_Config();
  TIM2_Config();
  TIM1_Config();
  ES_Init();
  ENC_InitEncoder();
  ADC_Config();
  Init_Chars();
  /* Initialize I/Os in Output Mode */
  GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);    //выход на тиристор
  GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);    //светодиод
  
  
  
  /* Initialize the Interrupt sensitivity */
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_FALL_ONLY);
  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
  /* Initialize I/Os in input Mode */
  GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_3, GPIO_MODE_IN_FL_IT);           //детектор нуля
 
  GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);        //кнопка
    
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  /* enable interrupts */
    enableInterrupts();

  while(1)
  {
    event = ES_GetEvent();
    if (event)
      ES_Dispatch(event);
   // GPIO_WriteReverse(GPIOC, (GPIO_Pin_TypeDef)GPIO_PIN_3);
  //  Delay_us(1000);
  }
}
void Delay_ms(uint16_t nCount)
{
  nCount = nCount*3182;
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void Delay_us(uint16_t nCount)
{
  nCount = nCount*3.127;
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
#ifdef USE_FULL_ASSERT 


/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}


#endif

INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)             //сигнал с детектора
{

  TIM2_SetCounter(0);                                   //сбросили счет таймера фазы
  TIM2_SetAutoreload(faza);                             //установили время задержки фазы
 
  if(BitIsClear(flags,REG_U_I) && BitIsSet(flags,STATE_ENABLE))                    //если  не стоит флаг ошибки
    TIM2_Cmd(ENABLE);                             // включаем таймер     
  
  
  //if(BitIsSet(flags,0))
  TIM1_Cmd(ENABLE);                                   //включаем таймер для выборок АЦП
}