/*
 * GccApplication1.c
 *
 * Created: 4/2/2022 3:15:08 PM
 * Author : mayaguru
 */ 

#include <avr/io.h>
#include <util/delay.h>




void Initialize(void) {
	DDRD |= (1<<DDD2);
	DDRD |= (1<<DDD3);
	DDRD |= (1<<DDD4);
	DDRD |= (1<<DDD5);
}
int main(void)
{
    /* Replace with your application code */
	Initialize();
    while (1) 
    {
		//front right
		PORTD |= (1<<PORTD4);
//		_delay_ms(1000);
//		PORTD &= ~(1<<PORTD4);
		
		//front left
		PORTD |= (1<<PORTD2);
//		_delay_ms(1000);
//		PORTD &= ~(1<<PORTD2);

		
		//back right
		PORTD |= (1<<PORTD5);
//		_delay_ms(1000);
//		PORTD &= ~(1<<PORTD5);

		
		//back left
		PORTD |= (1<<PORTD3);
//		_delay_ms(1000);
//		PORTD &= ~(1<<PORTD3);

		
    }
}

