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
double duty_cycle = 50;
int flag = 0;
int rising = 0;
int falling = 0;

tire* back_left;
tire* back_right;
tire* front_left;
tire* front_right;



void Initialize(void) {
	
	cli();
	
	//BLUE: BACK LEFT
	
	// backwards
	DDRD |= (1<<DDD2);
	
	//speed
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
	
	//backwards
	DDRB |= (1<<DDB0);
	
	//speed
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
	
	//TIMER 0 in fast PWM mode
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	
	//TIMER 1 in fast PWM mode
	TCCR1A |= (1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	//TIMER 2 in fast PWM mode
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<WGM21);
	TCCR2B &= ~(1<<WGM22);

	//TIMER 0 in fast PWM mode
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	
	// TIMER 0 prescale by 1024
	TCCR0B |= (1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);
	
	// TIMER 1 prescale by 1024
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
	
	// TIMER 2 prescale by 1024
	TCCR2B |= (1<<CS10);
	TCCR2B |= (1<<CS11);
	TCCR2B |= (1<<CS12);
	
	//TIMER 0 Output Compare
	TCCR0A |= (1<<COM0B1);
	TCCR0A &= ~(1<<COM0B0);
	
	OCR0B = (duty_cycle/100) * 255;
	
	TIMSK0 |= (1<<TOIE0);
	
	//TIMER 1 Output Compare
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);
	
	OCR1A = (duty_cycle/100) * 255;
	
	TIMSK1 |= (1<<TOIE1);
	
	//TIMER 2 Output Compare
	TCCR2A |= (1<<COM2A1);
	TCCR2A &= ~(1<<COM2A0);
	TCCR2A |= (1<<COM2B1);
	TCCR2A &= ~(1<<COM2B0);
	
	OCR2B = (duty_cycle/100) * 255;
	OCR2A = (duty_cycle/100) * 255;
	
	TIMSK2 |= (1<<TOIE2);
	
	
	sei();
	
}

ISR(TIMER0_OVF_vect) {
	OCR0B = (duty_cycle/100) * 255;
}

ISR(TIMER1_OVF_vect) {
	OCR1A = (duty_cycle/100) * 255;
}

ISR(TIMER2_OVF_vect) {
	OCR2B = (duty_cycle/100) * 255;
	OCR2A = (duty_cycle/100) * 255;

}

int main(void)
{
    /* Replace with your application code */
	
	Initialize();
	UART_init(BAUD_PRESCALER);
	
	
	back_left = malloc(sizeof(*back_left));
	init_tire(back_left, 0, PORTD3, PORTD4, PORTD2);
	
	
	front_left = malloc(sizeof(*front_left));
	init_tire(front_left, 0, PORTD5, PORTD7, PORTD6);
	
	
	
	front_right = malloc(sizeof(*front_right));
	init_tire(front_right, 1, PORTB1, PORTB2, PORTB0);

	back_right = malloc(sizeof(*back_right));
	init_tire(back_right, 1, PORTB3, PORTB5, PORTB4);
	
	int item = 0;
	//PORTD |= (1<<PORTD7);
	
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
			duty_cycle = 100;
			/*
			item = choose_item();
			sprintf(String, "item was %d \n", item);
			UART_putstring(String);
			deploy_item(item);
			*/
		} 
		
		sprintf(String, "ADC was %d\n", ADC);
		UART_putstring(String);
		
		
		/*
		move_car_forwards(front_right, back_right, front_left, back_left);
		
		
		_delay_ms(100);
		duty_cycle += 10;
		if (duty_cycle > 100) {
			duty_cycle = 0;
		}
		
		*/
	
		
	}
   
}