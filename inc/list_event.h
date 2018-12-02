#ifndef EVENT_LIST_H
#define EVENT_LIST_H

//коды событий
#define EVENT_NULL                    0
#define EVENT_KEY_ENTER               1
#define EVENT_KEY_ENTER_LONG          2
#define EVENT_KEY_ENTER_VERY_LONG     3
#define EVENT_ADC                     4
#define EVENT_ENCODER                 5

//коды событий таймеров
#define EVENT_300ms_TIMER        20
#define EVENT_250ms_TIMER        21
#define EVENT_0_5s_TIMER         22
#define EVENT_1s_TIMER           23
#define EVENT_2s_TIMER           24
#define EVENT_1ms_TIMER          25
#define EVENT_125ms_TIMER        26


//коды состояний
#define STATE_NO_CHANGE     0
#define STATE_LOW_F         1
#define STATE_HIGH_F        2
#define STATE_VOLUME        3
#define STATE_SLEEP         4
#define STATE_CH            5
#define STATE_SPECTR        6


//коды флагов
#define STATE_NO_CHANGE     0
#define ERROR_CURRENT       1
#define CHANGE_ADC_CHANEL   2
#define REG_U_I             3
#define F2                  4
#define STATE_ENABLE        5
#define STATE_SPECTR        6

#define NULL (void *)0

#endif //EVENT_LIST_H