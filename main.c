/*
 * GccApplication1.c
 *
 * Created: 4/4/2022 5:38:27 PM
 * Author : mayaguru
 */ 
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER ((F_CPU / (BAUD_RATE * 16UL)) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include "car.h"
#include <stdlib.h>
#include "uart.h"
#include <stdio.h>

char String[25];


void Initialize(void) {
	
	//BLUE: BACK LEFT
	
	// speed
	DDRD |= (1<<DDD2);
	
	//backwards
	DDRD |= (1<<DDD3);
	
	//forwards
	DDRD |= (1<<DDD4);
	
	//ORANGE: FRONT LEFT
	
	//speed
	DDRD |= (1<<DDD5);
	
	//backwards
	DDRD |= (1<<DDD6);
	
	//forwards
	DDRD |= (1<<DDD7);
	
	//WHITE: FRONT RIGHT
	
	//speed
	DDRB |= (1<<DDB0);
	
	//backwards
	DDRB |= (1<<DDB1);
	
	//forwards
	DDRB |= (1<<DDB2);
	
	//GREEN: BACK RIGHT
	
	//speed
	DDRB |= (1<<DDB3);
	
	//backwards
	DDRB |= (1<<DDB4);
	
	//forwards
	DDRB |= (1<<DDB5);
	
	// Turn Left
	DDRC &= ~(1<<DDC5);
	
	//Turn Right
	DDRC &= ~(1<<DDC4);
	
	// Move Forward
	DDRC &= ~(1<<DDC3);
	
}


int main(void)
{
    /* Replace with your application code */
	
	Initialize();
	UART_init(BAUD_PRESCALER);
	
	tire* back_left;
	back_left = malloc(sizeof(*back_left));
	init_tire(back_left, 0, PORTD2, PORTD4, PORTD3);
	
	tire* front_left;
	front_left = malloc(sizeof(*front_left));
	init_tire(front_left, 0, PORTD5, PORTD7, PORTD6);
	
	
	tire* front_right;
	front_right = malloc(sizeof(*front_right));
	init_tire(front_right, 1, PORTB0, PORTB2, PORTB1);
	
	tire* back_right;
	back_right = malloc(sizeof(*back_right));
	init_tire(back_right, 1, PORTB3, PORTB5, PORTB4);
	
	while(1) {
		
		if (PINC & (1<<PINC5)) {
			turn_left(front_right, back_right, front_left, back_left);
		}
		if (PINC & (1<<PINC4)) {
			turn_right(front_right, back_right, front_left, back_left);
		}
		if (PINC & (1<<PINC3)) {
			move_car_forwards(front_right, back_right, front_left, back_left);
		}
		else {
			stop(front_right, back_right, front_left, back_left);
		}
		
	}
   
}