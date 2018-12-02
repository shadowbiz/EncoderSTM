#ifndef	BUTTONS_h
#define	BUTTONS_h

#include "event-system.h"
#include "list_event.h"
#include "stm8s_conf.h"
#include "iostm8s003f3.h"

//порт, к которому подключены кнопки
#define PORT_BUTTON 	PC_ODR
#define PIN_BUTTON 	PC_IDR
#define DDRX_BUTTON 	PC_DDR
//события нажатия кнопок
#define KEY_NULL                0
#define KEY_ENTER_LONG          1
#define KEY_ENTER_VERY_LONG     2
#define KEY_ENTER               3
#define KEY_ENTER_1             4

//номера выводов, к которым подключены кнопки

#define ENTER          3
//сколько циклов опроса кнопка должна удерживаться
#define THRESHOLD 50	        //циклов опроса для антидребезга
#define THRESHOLD2 600	        //длительне нажатие		
#define THRESHOLD3 2000		//очень длительне нажатие
#define THRESHOLD4 2500		//очень очень длительне нажатие
/**************************************************************************
*   Function name : BUT_Init
*   Returns :       нет
*   Parameters :    нет
*   Purpose :       инициализация портов ввода/вывода
*                   вызывается обычно в начале main`a
****************************************************************************/
void BUT_Init(void);

/**************************************************************************
*   Function name : BUT_Debrief
*   Returns :       нет
*   Parameters :    нет
*   Purpose :       опрашивает кнопки. вызывается обычно из прерывания
*                   если кнопка нажата в течении 20 прерываний,
*                   ее номер записывается в буфер
****************************************************************************/
void BUT_Debrief(void);
/**************************************************************************
*   Function name : BUT_GetKey
*   Returns :       номер нажатой кнопки
*   Parameters :    нет
*   Purpose :       возвращает содержимое кнопочного буфера
*                   при этом буфер очищается
*                   вызывается обычно в main`e в цикле while
*
****************************************************************************/
void BUT_GetKey(void);
#endif //BUTTONS_H
