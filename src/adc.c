#include "adc.h"
 
unsigned int buf =0;
extern int current_zad;
extern unsigned int count,faza;
extern  unsigned int current;
extern unsigned int buf_curr;


unsigned int buf_adc[100] = 0;
unsigned int buf_adc_v = 0;
extern unsigned char count_adc,flags;
void ADC_Config()
{
  /*  Init GPIO for ADC2 */
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_IN_FL_NO_IT);
  
  /* De-Init ADC peripheral*/
  ADC1_DeInit();

  /* Init ADC2 peripheral */
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_6, ADC1_PRESSEL_FCPU_D18, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL6,\
            DISABLE);

  /* Enable EOC interrupt */
  ADC1_ITConfig(ADC1_IT_EOCIE,ENABLE);

  /*Start Conversion */
  ADC1_StartConversion();
  
 // ADC1_Cmd(DISABLE);
}

void Change_Chanel_ADC1(ADC1_Channel_TypeDef ADC1_Channel)
{
  /* Clear the ADC1 channels */
  ADC1->CSR &= (uint8_t)(~ADC1_CSR_CH);
  /* Select the ADC1 channel */
  ADC1->CSR |= (uint8_t)(ADC1_Channel);
  }

INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{
 // GPIO_WriteHigh(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_4);
  
  if(BitIsSet(ADC1->CSR,0))     //если канал 5 АЦП, то меряли напругу
  {
  buf_adc[count_adc] = ADC1_GetConversionValue();       //берем значение АЦП
  if(++count_adc == 50)                                 //копим в буфере
  {     
    count_adc = 0;              
 //   TIM1_Cmd(DISABLE);                                  //выключаем таймер для выборок
    ClearBit(flags,0);
    ES_PlaceEvent(EVENT_ADC);                           //
   // GPIO_WriteLow(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_4);
    }
  }
  else                          //иначе, канал 6 б меряли ток
  {
    buf_adc_v = ADC1_GetConversionValue(); 
    ES_PlaceEvent(EVENT_ADC);
   }

 ADC1_ClearFlag(ADC1_FLAG_EOC);
}