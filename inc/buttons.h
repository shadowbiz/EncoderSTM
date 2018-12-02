#ifndef	BUTTONS_h
#define	BUTTONS_h

#include "event-system.h"
#include "list_event.h"
#include "stm8s_conf.h"
#include "iostm8s003f3.h"

//����, � �������� ���������� ������
#define PORT_BUTTON 	PC_ODR
#define PIN_BUTTON 	PC_IDR
#define DDRX_BUTTON 	PC_DDR
//������� ������� ������
#define KEY_NULL                0
#define KEY_ENTER_LONG          1
#define KEY_ENTER_VERY_LONG     2
#define KEY_ENTER               3
#define KEY_ENTER_1             4

//������ �������, � ������� ���������� ������

#define ENTER          3
//������� ������ ������ ������ ������ ������������
#define THRESHOLD 50	        //������ ������ ��� ������������
#define THRESHOLD2 600	        //��������� �������		
#define THRESHOLD3 2000		//����� ��������� �������
#define THRESHOLD4 2500		//����� ����� ��������� �������
/**************************************************************************
*   Function name : BUT_Init
*   Returns :       ���
*   Parameters :    ���
*   Purpose :       ������������� ������ �����/������
*                   ���������� ������ � ������ main`a
****************************************************************************/
void BUT_Init(void);

/**************************************************************************
*   Function name : BUT_Debrief
*   Returns :       ���
*   Parameters :    ���
*   Purpose :       ���������� ������. ���������� ������ �� ����������
*                   ���� ������ ������ � ������� 20 ����������,
*                   �� ����� ������������ � �����
****************************************************************************/
void BUT_Debrief(void);
/**************************************************************************
*   Function name : BUT_GetKey
*   Returns :       ����� ������� ������
*   Parameters :    ���
*   Purpose :       ���������� ���������� ���������� ������
*                   ��� ���� ����� ���������
*                   ���������� ������ � main`e � ����� while
*
****************************************************************************/
void BUT_GetKey(void);
#endif //BUTTONS_H
