#include "Driver_RTC.h"
#include <stdlib.h>

time gettime(void){
	time t;
	char* data = malloc(6);  // on a besoins de 6 octets pour connaitre la date
	I2C_getBytes(0, RTC_ADDRESS, data);
	t.second = (data[0] & 0x0F) + 10*((data[0]>>4)&0x7);
	t.second = (data[0] & 0x0F) + 10*((data[0]>>4)&0x7);
	
	return t;
}