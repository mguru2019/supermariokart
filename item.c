/*
 * item.c
 *
 * Created: 4/6/2022 2:39:48 PM
 *  Author: mayaguru
 */ 

#include "item.h"
#include "car.h"
#include "LED.h"
#include "character.h"

int choose_item(void) {
	
	if (!has_item) {
		int i = rand() % 3 + 1;
		has_item = 1;
		dc_item = i * 10 + 10;
		return i;
	}
	return 0;

}


void deploy_item(int item, tire* fr, tire* br, tire* fl, tire* bl) {
	if (has_item == 1) {
		if (item == MUSHROOM) {
			speed_up(fr,br,fl,bl);
			_delay_ms(2000);
			slow_down(fr,br,fl,bl);
		}
		else if (item == BANANA) {
			_delay_ms(1000);
			spin(fr,br,fl,bl);
		}
		else if (item == STAR) {
			speed_up(fr,br,fl,bl);
			for(int i = 0; i < 10; i++) {
				random_pwm();
				_delay_ms(500);
			}
			slow_down(fr,br,fl,bl);
			light_led(user_character);
		}
		has_item = 0;
		dc_item = 0;
	}

}
