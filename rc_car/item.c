/*
 * item.c
 *
 * Created: 4/21/2022 3:06:39 PM
 *  Author: kasoo
 */ 

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
#include "communication.h"

int choose_item(void) {
	
	if (!has_item) {
		int i = rand() % 9 + 1;
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
		else {
			ready_to_transmit();
			_delay_ms(10);
			send_item(item);
		}
		has_item = 0;
		dc_item = 0;
		item_sent();
	}

}

void receive_item(int item, tire* fr, tire* br, tire* fl, tire* bl) {
	if (item == BULLET) {
		stop(fr,br,fl,bl);
		_delay_ms(3000);
	}
	else if (item == REDSHELL) {
		spin(fr,br,fl,bl);
	}
	else if (item == GREENSHELL) {
		int prob = rand() % 100;
		if (prob > 60) {
			spin(fr, br, fl, bl);
		}
	}
	else if (item == LIGHTNING) {
		slide_left(fr,br,fl,bl);
		_delay_ms(500);
		slide_right(fr,br,fl,bl);
		_delay_ms(500);
		slow_down(fr,br,fl,bl);
		_delay_ms(2000);
		speed_up(fr,br,fl,bl);
	}
	else if (item == POW) {
		spin(fr,br,fl,bl);
		spin(fr,br,fl,bl);
	}
	else if (item == BLUESHELL) {
		move_car_backwards(fr,br,fl,bl);
		_delay_ms(2000);
	}
}
