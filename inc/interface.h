#ifndef INTERFACE_H
#define INTERFACE_H

#include "stm8s_conf.h"
#include "iostm8s003f3.h"
#include "lcd_lib.h"
#include "bits_macros.h"
#include "stm8s_tim4.h"


void Init_Chars(void);
void Change_Disp(void);
void GUI_Adc(void);
void GUI_Button(void);
void Init_Chars(void);
#endif // INTERFACE_H