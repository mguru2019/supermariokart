/*
 * LED.h
 *
 * Created: 4/12/2022 6:40:15 PM
 *  Author: mayaguru
 */ 


#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#define RAND_MAX 255
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void init_led();
void pwm(int pin,int num);



#endif /* LED_H_ */