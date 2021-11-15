#ifndef IMU_H
#define IMU_H

#include "stm32f10x.h"

/* Renvoie un booléen : 1 si le bateau a un roulis de plus de 40°, 0 sinon*/
int IsCapsizing(void);
void Initialize_IMU(void);

#endif
