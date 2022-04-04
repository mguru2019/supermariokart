/*
 * GccApplication1.c
 *
 * Created: 4/4/2022 5:38:27 PM
 * Author : mayaguru
 */ 

#include <avr/io.h>
#include <util/delay.h>

void Initialize(void) {
	
	//speed for front left
	DDRD |= (1<<DDD0);
	
	//speed for front right
	DDRD |= (1<<DDD1);
	
	//backwards for front right
	DDRD |= (1<<DDD2);
	
	//forwards for front right
	DDRD |= (1<<DDD3);
	
	//backwards for front left
	DDRD |= (1<<DDD4);
	
	//forwards for front left
	DDRD |= (1<<DDD5);
	
	//forwards for back right
	DDRD |= (1<<DDD6);
	
	//backwards for back right
	DDRD |= (1<<DDD7);
	
	//speed for back right
	DDRB |= (1<<DDB0);
	
	//forwards for back left
	DDRB |= (1<<DDB1);
	
	//backwards for back left
	DDRB |= (1<<DDB2);
	
	//speed for back left
	DDRB |= (1<<DDB3);
	
	
}

int main(void)
{
    /* Replace with your application code */
	
	//Initialize();
	
	DDRB |= (1<<DDB5);
    while (1) 
    {
		PORTB |= (1<<PORTB5);
		_delay_ms(1000);
		PORTB &= ~(1<<PORTB5);
    }
}

