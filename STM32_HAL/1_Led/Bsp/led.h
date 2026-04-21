#ifndef _LED_H_
#define _LED_H_


#include "main.h"

#define LED_ON	1

#define LED_OFF	0

extern uint8_t Led_Status;



void Led_Init(void);

void Led_Set(_Bool status);


#endif


