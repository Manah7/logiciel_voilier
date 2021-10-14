#ifndef COM_H
#define COM_H

#include "stm32f10x.h"
#include "driver_Timer.h"

//Configure l'UART
void Config_UART(USART_TypeDef * UART_Par);

//Configure l'envoi de message
void Init_Message_Sending(int delay);

//Configuerer la réception de messages
//void Init_Message_Receiving();

//Envoi de messages
void Send_Message(const char * message[]);



#endif