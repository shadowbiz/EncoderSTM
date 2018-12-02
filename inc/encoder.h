#ifndef	encoder_h
#define	encoder_h
#include "stm8s_conf.h"
#include "iostm8s003f3.h"
#include "bits_macros.h"
//_________________________________________
//порт и выводы к которым подключен энкодер
#define PORT_Enc 	PORTB
#define PIN_Enc 	PINB
#define DDR_Enc 	DDRB
#define Pin1_Enc 	4
#define Pin2_Enc 	5
//______________________
#define RIGHT_SPIN 0x01 
#define LEFT_SPIN 0xff


//это для наглядности кода
#define b00000011 3
#define b11010010 210
#define b11100001 225

#define MAX_VALUE 5000
#define MIN_VALUE  10

void ENC_InitEncoder(void);
void ENC_PollEncoder(void);
unsigned char ENC_GetStateEncoder(void);
#endif  //encoder_h
