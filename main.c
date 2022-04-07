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
#include <avr/interrupt.h>
#include "car.h"
#include "item.h"
#include <stdlib.h>
#include "uart.h"
#include <stdio.h>

char String[25];
float duty_cycle = 0.75;
int flag = 0;
int rising = 0;
int falling = 0;

tire* back_left;
tire* back_right;
tire* front_left;
tire* front_right;



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
	
	//JOYSTICK CONTROLS
	
	// Turn Left
	DDRC &= ~(1<<DDC5);
	
	//Turn Right
	DDRC &= ~(1<<DDC4);
	
	// Move Forward
	DDRC &= ~(1<<DDC3);
	
	//DRIFT CONTROL
	
	DDRC &= ~(1<<DDC2);
	
	//PHOTORESISTOR
	
	
	PRR &= ~(1<<PRADC);
	
	
	//Select the reference voltage as AVcc
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	//Set the ADC Clock prescaler to 16M/128 = 125kHz (clock must be between 50 and 200kHz)
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
	
	//Select Pin A0 channel to read
	ADMUX &= ~(1<<MUX0);
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX3);
	
	//Set ADC to be free running
	ADCSRA |= (1<<ADATE);
	ADCSRB &= ~(1<<ADTS0);
	ADCSRB &= ~(1<<ADTS1);
	ADCSRB &= ~(1<<ADTS2);
	
	//Disable input buffer
	DIDR0 |= (1<<ADC0D);
	
	//Enable ADC
	ADCSRA |= (1<<ADEN);
	
	//Start conversion
	ADCSRA |= (1<<ADSC);
	
}




int main(void)
{
    /* Replace with your application code */
	
	Initialize();
	UART_init(BAUD_PRESCALER);
	
	
	back_left = malloc(sizeof(*back_left));
	init_tire(back_left, 0, PORTD2, PORTD4, PORTD3);
	
	
	front_left = malloc(sizeof(*front_left));
	init_tire(front_left, 0, PORTD5, PORTD7, PORTD6);
	
	
	
	front_right = malloc(sizeof(*front_right));
	init_tire(front_right, 1, PORTB0, PORTB2, PORTB1);

	back_right = malloc(sizeof(*back_right));
	init_tire(back_right, 1, PORTB3, PORTB5, PORTB4);
	
	int item = 0;
	
	while(1) {
		
		if (PINC & (1<<PINC5) && PINC & (1<<PINC3) && PINC & (1<<PINC2)) {
			slide_right(front_right, back_right, front_left, back_left);
		}
		else if (PINC & (1<<PINC4) && PINC & (1<<PINC3) && PINC & (1<<PINC2))  {
			slide_left(front_right, back_right, front_left, back_left);
		}
		else if (PINC & (1<<PINC5) && PINC & (1<<PINC3) && ~(PINC & (1<<PINC2))) {
			turn_left(front_right, back_right, front_left, back_left);
		}
		else if (PINC & (1<<PINC4) && PINC & (1<<PINC3) && ~(PINC & (1<<PINC2))) {
			turn_right(front_right, back_right, front_left, back_left);
		}
	
		else if (PINC & (1<<PINC3)) {
			move_car_forwards(front_right, back_right, front_left, back_left);
		}
		else {
			stop(front_right, back_right, front_left, back_left);
		}
		
		if (ADC > 900) {
			item = choose_item();
			sprintf(String, "item was %d \n", item);
			UART_putstring(String);
			deploy_item(item);
		}
	
		
	}
   
}