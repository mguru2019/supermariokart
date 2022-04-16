/*
 * GccApplication1.c
 *
 * Created: 4/4/2022 5:38:27 PM
 * Author : mayaguru
 */ 

//"C:\avrdude\avrdude.conf" -v -p atmega2560 -c wiring -P COM13 -b 115200 -D -U flash:w:"$(ProjectDir)Debug\$(TargetName).hex":i"

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
#include "LED.h"
#include "character.h"

char String[25];
int flag = 0;
int rising = 0;
int falling = 0;

tire* back_left;
tire* back_right;
tire* front_left;
tire* front_right;

void Initialize(void) {
	
	cli();
	
	init_state();
	has_item = 0;
	//BLUE: BACK LEFT
	
	// backwards
	DDRL |= (1<<DDL6);
	
	//speed
	DDRE |= (1<<DDE5);
	
	//forwards
	DDRL |= (1<<DDL7);
	
	//ORANGE: FRONT LEFT
	
	//speed
	DDRE |= (1<<DDE3);
	
	//backwards
	DDRL |= (1<<DDL4);
	
	//forwards
	DDRL |= (1<<DDL5);
	
	//WHITE: FRONT RIGHT
	
	//backwards
	DDRL |= (1<<DDL0);
	
	//speed
	DDRB |= (1<<DDB4);
	
	//forwards
	DDRL |= (1<<DDL1);
	
	//GREEN: BACK RIGHT
	
	//speed
	DDRB |= (1<<DDB5);
	
	//backwards
	DDRL |= (1<<DDL2);
	
	//forwards
	DDRL |= (1<<DDL3);
	
	//JOYSTICK CONTROLS
	
	// Turn Left
	DDRF &= ~(1<<DDF5);
	
	//Turn Right
	DDRF &= ~(1<<DDF4);
	
	// Move Forward
	DDRF &= ~(1<<DDF3);
	
	//DRIFT CONTROL
	
	DDRF &= ~(1<<DDF2);
	
	init_dc();
	
	//PHOTORESISTOR
	DDRA &= ~(1<<DDA7);
	item = 0;
	PRR0 &= ~(1<<PRADC);
	DDRE |= (1<<DDE4);
	
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
	
	//TIMER 1 in fast PWM mode
	TCCR1A |= (1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	//TIMER 2 in fast PWM mode
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<WGM21);
	TCCR2B &= ~(1<<WGM22);

	//TIMER 3 in fast PWM mode
	TCCR3A |= (1<<WGM30);
	TCCR3A &= ~(1<<WGM31);
	TCCR3B |= (1<<WGM32);
	TCCR3B &= ~(1<<WGM33);
	
	// TIMER 3 prescale by 1024
	TCCR3B |= (1<<CS30);
	TCCR3B &= ~(1<<CS31);
	TCCR3B |= (1<<CS32);
	
	// TIMER 1 prescale by 1024
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
	
	// TIMER 2 prescale by 1024
	TCCR2B |= (1<<CS10);
	TCCR2B |= (1<<CS11);
	TCCR2B |= (1<<CS12);
	
	//TIMER 3 Output Compare
	TCCR3A |= (1<<COM3A1);
	TCCR3A &= ~(1<<COM3A0);
	
	TCCR3A |= (1<<COM3B1);
	TCCR3A &= ~(1<<COM3B0);
	
	TCCR3A |= (1<<COM3C1);
	TCCR3A &= ~(1<<COM3C0);
		
	OCR3A = (dc_fl/100) * 255;
	OCR3C = (dc_bl/100) * 255;
	OCR3B = (dc_item/100) * 255;
	
	TIMSK3 |= (1<<TOIE3);
	
	//TIMER 1 Output Compare
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);
	
	OCR1A = (dc_br/100) * 255;
	
	TIMSK1 |= (1<<TOIE1);
	
	//TIMER 2 Output Compare
	TCCR2A |= (1<<COM2A1);
	TCCR2A &= ~(1<<COM2A0);
	
	OCR2A = (dc_fr/100) * 255;
	
	TIMSK2 |= (1<<TOIE2);
	
	init_led();
	
	user_character = 0;
	sei();
	
}

ISR(TIMER3_OVF_vect) {
	OCR3A = (dc_fl/100) * 255;
	OCR3C = (dc_bl/100) * 255;
	OCR3B = (dc_item/100) * 255;
}

ISR(TIMER1_OVF_vect) {
	OCR1A = (dc_br/100) * 255;
}

ISR(TIMER2_OVF_vect) {
	OCR2A = (dc_fr/100) * 255;

}

int main(void)
{
    /* Replace with your application code */
	srand(time(NULL));
	Initialize();
	UART_init(BAUD_PRESCALER);
	
	back_left = malloc(sizeof(*back_left));
	init_tire(back_left, 0, PE5, PL7, PL6, 0);
	
	
	front_left = malloc(sizeof(*front_left));
	init_tire(front_left, 0, PE3, PL5, PL4, 0);
	
	
	front_right = malloc(sizeof(*front_right));
	init_tire(front_right, 1, PB4, PL1, PL0, 0);

	back_right = malloc(sizeof(*back_right));
	init_tire(back_right, 1, PB5, PL3, PL2, 0);
	
	//user_character = choose_character();
	while(1) {
		
		if (game_state == 0) { 
		choose_character();	
		light_led(selected_character);
		character_locked(front_right, back_right, front_left, back_left);
		} 
		
		else if (game_state == 1) { 
			light_led(user_character);
			
			if (ADC > 900 && has_item == 0) {
				item = choose_item();
				sprintf(String, "Item is: %d \n", item);
				UART_putstring(String);							
			}
			if (PINA & (1<<PINA7)) {
				sprintf(String, "In conditional \n");
				UART_putstring(String);
				deploy_item(item, front_right, back_right, front_left, back_left);
			}
			
			
			if (PINF & (1<<PINF5) && PINF & (1<<PINF3) && PINF & (1<<PINF2)) {
				slide_right(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF4) && PINF & (1<<PINF3) && PINF & (1<<PINF2))  {
				slide_left(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF5) && PINF & (1<<PINF3) && ~(PINF & (1<<PINF2))) {
				veer_left(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF4) && PINF & (1<<PINF3) && ~(PINF & (1<<PINF2))) {
				veer_right(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF4) && ~(PINF & (1<<PINF3)) && (PINF & (1<<PINF2))) {
				init_dc();
				slide_right(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF5) && ~(PINF & (1<<PINF3)) && (PINF & (1<<PINF2))) {
				init_dc();
				slide_left(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF5) && ~(PINF & (1<<PINF3)) && ~(PINF & (1<<PINF2))) {
				sprintf(String, "Got Here: %d \n", selected_character);
				UART_putstring(String);
				init_dc();
				turn_left(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF4) && ~(PINF & (1<<PINF3)) && ~(PINF & (1<<PINF2))) {
				init_dc();
				turn_right(front_right, back_right, front_left, back_left);
			}
			else if (PINF & (1<<PINF3)) {
				init_dc();
				move_car_forwards(front_right, back_right, front_left, back_left);
			}
			else {
				init_dc();
				stop(front_right, back_right, front_left, back_left);
			}
		}
	} 
}
