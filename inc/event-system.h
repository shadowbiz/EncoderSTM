//***************************************************************************
#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "stm8s_conf.h"
#include "iostm8s003f3.h"
#include "lcd_lib.h"
#include "bits_macros.h"
#include "stm8s_tim4.h"
#include "list_event.h"  
#include "interface.h" 

#define SIZE_BUF 16       //����������� ������/������� �������

void ES_Init(void);                       //�������������
unsigned char ES_GetEvent(void);           //����� ��� �������  
void ES_PlaceEvent(unsigned char event);   //���������� �������
void ES_Dispatch(unsigned char currentEvent);     //����� ����������
void ChangeStatus(unsigned char data);
#endif // EVENT_SYSTEM_H