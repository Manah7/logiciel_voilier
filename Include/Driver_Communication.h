#ifndef COM_H
#define COM_H

#include "stm32f10x.h"
//Configure l'envoi de message
void InitMessageSending(int delay);
void InitMessageReceiving();
void SendMessage(char * message[], int size);
//à mettre dans le .c
void CallbackMessageReceiving();
void CallBackMessageSending();
void SendChar(char character);


#endif