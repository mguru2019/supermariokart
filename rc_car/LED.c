/*
 * LED.c
 *
 * Created: 4/12/2022 6:40:34 PM
 *  Author: mayaguru
 */ 
#include "LED.h"

void init_led() {
	DDRH |= (1<<DDH3);
	DDRH |= (1<<DDH4);
	DDRH |= (1<<DDH5);
	
	TCCR4B |= (1<<CS40);
	TCCR4B |= (1<<CS41); //prescalar /64
	
	TCCR4A |= (1<<WGM40);
	TCCR4A &= ~(1<<WGM41);
	TCCR4B |= (1<<WGM42);
	TCCR4B &= ~(1<<WGM43);
	
	TCCR4A |= (1<<COM4A1);
	TCCR4A &= ~(1<<COM4A0);//fast pwm, non inverted
	
	TCCR4A |= (1<<COM4B1);
	TCCR4A &= ~(1<<COM4B0);//fast pwm, non inverted
	
	TCCR4A |= (1<<COM4C1);
	TCCR4A &= ~(1<<COM4C0);//fast pwm, non inverted
}
void pwm(int pin,int num){
	switch(pin){
		case 0:	//RED
		PORTH |= (1<<PH3);
		PORTH &= ~(1<<PH4);
		PORTH &= ~(1<<PH5);
		OCR4A=num;
		break;
		case 1: //GREEN
		PORTH |= (1<<PH4);
		PORTH &= ~(1<<PH3);
		PORTH &= ~(1<<PH5);
		OCR4B=num;
		break;
		case 2: //BLUE
		PORTH |= (1<<PH5);
		PORTH &= ~(1<<PH3);
		PORTH &= ~(1<<PH4);
		OCR4C=num;
		break;
	}
}

void random_pwm() {
	int red = rand();
	int green = rand();
	int blue = rand();
	
	pwm(0,red);
	pwm(1,green);
	pwm(2,blue);
	
}

void led_off() {
	PORTH &= ~(1<<PH5);
	PORTH &= ~(1<<PH3);
	PORTH &= ~(1<<PH4);
}