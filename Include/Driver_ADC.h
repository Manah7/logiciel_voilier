#ifndef MYADC_H
#define MYADC_H

#include "stm32f10x.h"
#include "Driver_Timer.h"

void configADC1(int channel);

void calibrateADC1(void);

void setExternalTriggerADC1(void);

int getADC1Value(void);
		
#endif
