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

tire* back_left;
tire* back_right;
tire* front_left;
tire* front_right;

int has_item = 0;

int choose_item(void) {
	
	if (!has_item) {
		int item = rand() % 9 + 1;
		has_item = 1;
		return item;
	}
	return 0;

}

void deploy_item(int item) {
	
	back_left = malloc(sizeof(*back_left));
	init_tire(back_left, 0, PE5, PL7, PL6, 0);
	
	
	front_left = malloc(sizeof(*front_left));
	init_tire(front_left, 0, PE3, PL5, PL4, 0);
	
	
	front_right = malloc(sizeof(*front_right));
	init_tire(front_right, 1, PB4, PL1, PL0, 0);

	back_right = malloc(sizeof(*back_right));
	init_tire(back_right, 1, PB5, PL3, PL2, 0);
	
	if (item == MUSHROOM) {
		speed_up(front_right,back_right,front_left,back_left);
		_delay_ms(1000);
		slow_down(front_right,back_right,front_left,back_left);
	}
	else if (item == BANANA) {
		spin(front_right,back_right,front_left,back_left);
	}
/*	else if (item == STAR) {
		speed_up(front_right,back_right,front_left,back_left);
		random_pwm();
		_delay_ms(5000);
		slow_down(front_right,back_right,front_left,back_left);
		light_led(character); 
	} */
	has_item = 0;
}
