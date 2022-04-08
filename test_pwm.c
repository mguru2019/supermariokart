/*
 * GccApplication1.c
 *
 * Created: 4/7/2022 10:46:20 PM
 * Author : mayaguru
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


double duty_cycle = 0; 

void Initialize(void) {
	cli();
	DDRD |= (1<<DDD5);
		
	//clock in PWM mode
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
		
	
	TCCR0B |= (1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);
		
		
	TCCR0A |= (1<<COM0B1);
	TCCR0A &= ~(1<<COM0B0);
		
	OCR0B = (duty_cycle/100) * 255;
		
		
	TIMSK0 |= (1<<TOIE0);
	
	sei();
	
}

ISR(TIMER0_OVF_vect) {
	OCR0B = (duty_cycle/100) * 255;
}



int main(void)
{
    /* Replace with your application code */
	Initialize();
    while (1) 
    {
		_delay_ms(100);
		duty_cycle += 10;
		if (duty_cycle > 100) {
			duty_cycle = 0;
		}
    }
}
