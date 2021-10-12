#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "Driver_ADC.h"

void test_gpio () {
	MyGPIO_Struct_TypeDef button;
	MyGPIO_Struct_TypeDef led;
	
	button.GPIO = GPIOC;
	button.GPIO_Conf = In_Floating;
	button.GPIO_Pin = 8;
	
	led.GPIO = GPIOC;
	led.GPIO_Conf = Out_Ppull;
	led.GPIO_Pin = 10;
	
	RCC->APB2ENR |=(0x01 << 2)|(0x01 << 3)|(0x01 << 4);
	
	MyGPIO_Init(&button);
	MyGPIO_Init(&led);
	
	do {
		if (MyGPIO_Read(button.GPIO, button.GPIO_Pin)) {
			MyGPIO_Set(led.GPIO, led.GPIO_Pin);
		} else {
			MyGPIO_Reset(led.GPIO, led.GPIO_Pin);
		}
	} while (1);
}


// Declarations
MyGPIO_Struct_TypeDef led;

MyTimer_Struct_TypeDef timer1;
MyTimer_Struct_TypeDef timer2;
MyGPIO_Struct_TypeDef pb0;

int pourcentage;

void callback() {
	//MyGPIO_Toggle(led.GPIO, led.GPIO_Pin);
	pourcentage = (pourcentage + 10) % 100;
	Set_pwm_percentage(timer1.Timer, pourcentage, 1);
}


void test_timer(){
	// T_timer = T_horloge * prescaler[1 | 2^16] * autoreload
	// autoreload = T_timer / (prescaler * T_horloge)
	// autoreload = 0.5 / (10000 * 1/72000000) = 3600
	
	// Confuguration du timer
	timer2.Timer = TIM2;
	timer2.ARR = 1000; // Autoreload
	timer2.PSC = 7200; // Prescaler
	
	MyTimer_Base_Init(&timer2);
	MyTimer_Base_Start(timer2.Timer);
	
	// Configuration du GPIO pour faire clignoter la LED
	led.GPIO = GPIOC;
	led.GPIO_Conf = AltOut_Ppull;
	led.GPIO_Pin = 10;
	MyGPIO_Init(&led);
	
	
	// Config interuption
	Setup_Callback(&callback, timer2.Timer);
	MyTimer_ActiveIT(timer2.Timer, 8);
	
	//do {} while (1);
}

void test_pwm(){
	// Led sur PA6
	timer1.Timer = TIM3;
	// autoreload = T_timer / (prescaler * T_horloge)
	// = 1 / (p * 1/72M)
	timer1.PSC = 10000;
	timer1.ARR = 3600;
	
	MyTimer_Base_Init(&timer1);
	MyTimer_Base_Start(timer1.Timer);
	MyTimer_PWM(timer1.Timer, 1);
	Set_pwm_percentage(timer1.Timer, 10, 1);
	
	do {} while (1);
}

int result;

void test_adc(){
	pb0.GPIO = GPIOB;
	pb0.GPIO_Conf = In_Analog;
	pb0.GPIO_Pin = 0;
	MyGPIO_Init(&pb0);
	
	configADC1(8);
	do {
		result = getADC1Value();
	} while (1);
}

int main () {	
  RCC->APB2ENR |=(0x01 << 2)|(0x01 << 3)|(0x01 << 4);
	
	//test_gpio();
	//test_timer();
	//test_pwm();
	test_adc();
}