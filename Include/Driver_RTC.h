#ifndef RTC_H
#define RTC_H

#include "stm32f10x.h"
#include "Driver_I2C.h"

typedef struct{
    int year;
    int month;
    int day;
    int minute;
    int second;
} time;

void RTC_init(void);

uint32_t I2C_getdata(uint32_t Register_address, uint16_t device_address);

time RTC_gettime (void);

#endif
