/*
 * GccApplication1.c
 *
 * Created: 4/4/2022 5:38:27 PM
 * Author : mayaguru
 */ 

#include <avr/io.h>
#include <util/delay.h>

void Initialize(void) {
	
	//BLUE: BACK LEFT
	
	// speed
	DDRD |= (1<<DDD2);
	
	//forwards
	DDRD |= (1<<DDD3);
	
	//backwards
	DDRD |= (1<<DDD4);
	
	//ORANGE: FRONT LEFT
	
	//speed
	DDRD |= (1<<DDD5);
	
	//forwards
	DDRD |= (1<<DDD6);
	
	//backwards
	DDRD |= (1<<DDD7);
	
	//WHITE: FRONT RIGHT
	
	//speed
	DDRB |= (1<<DDB0);
	
	//forwards
	DDRB |= (1<<DDB1);
	
	//backwards
	DDRB |= (1<<DDB2);
	
	//GREEN: BACK RIGHT
	
	//speed
	DDRB |= (1<<DDB3);
	
	//forwards
	DDRB |= (1<<DDB4);
	
	//backwards
	DDRB |= (1<<DDB5);
}

int main(void)
{
    /* Replace with your application code */
	
	Initialize();
	
	while(1) {
		PORTD |= (1<<PORTD2);
		PORTD &= ~(1<<PORTD3);
		PORTD |= (1<<PORTD4);
		
		PORTD |= (1<<PORTD5);
		PORTD &= ~(1<<PORTD6);
		PORTD |= (1<<PORTD7);
		
		PORTB |= (1<<PORTB0);
		PORTB &= ~(1<<PORTB1);
		PORTB |= (1<<PORTB2);
		
		PORTB |= (1<<PORTB3);
		PORTB &= ~(1<<PORTB4);
		PORTB |= (1<<PORTB5);

		
	}
   
}
