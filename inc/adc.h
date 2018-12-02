#include "stm8s_conf.h"
#include "iostm8s003f3.h"
#include "lcd_lib.h"
#include "bits_macros.h"
#include "stm8s_tim4.h"
#include "event-system.h"

void ADC_Config(void);
void Change_Chanel_ADC1(ADC1_Channel_TypeDef ADC1_Channel);