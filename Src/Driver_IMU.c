#include "Driver_IMU.h"
#include "Driver_I2C.h"


void read(){	char valeurs[6];
	I2C_getBytes(0x32,IMU_ADDRESS,valeurs);
}


void Initialize_IMU(){
	I2C_Init(100000, 1);

	
}