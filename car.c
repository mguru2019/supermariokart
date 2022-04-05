/*
 * car.c
 *
 * Created: 4/5/2022 2:04:18 PM
 *  Author: mayaguru
 */ 
#include "car.h"

void init_tire(tire* t, int is_right, uint8_t speed_pin, uint8_t forwards_pin, uint8_t backwards_pin) {
	t->speed = speed_pin;
	t->is_right = is_right;
	t->forwards = forwards_pin;
	t->backwards = backwards_pin;
}

void move_tire_forwards(tire* t) {
	if (t->is_right) {
		PORTB |= (1<<t->speed);
		PORTB |= (1<<t->forwards);
		PORTB &= ~(1<<t->backwards);
	} else {
		PORTD |= (1<<t->speed);
		PORTD |= (1<<t->forwards);
		PORTD &= ~(1<<t->backwards);
	}
}

void move_tire_backwards(tire* t) {
	if (t->is_right) {
		PORTB |= (1<<t->speed);
		PORTB &= ~(1<<t->forwards);
		PORTB |= (1<<t->backwards);
		} else {
		PORTD |= (1<<t->speed);
		PORTD &= ~(1<<t->forwards);
		PORTD |= (1<<t->backwards);
	}
}
void turn_left(tire* fr, tire* br, tire* fl, tire* bl) {
	//front right forwards
	//back left backwards
	
	//OR
	
	//front left backwards
	//back right forwards
	move_tire_forwards(fr);
	move_tire_backwards(bl);
	move_tire_backwards(fl);
	move_tire_forwards(br);
	
	
}
void stop_tire(tire* t) {
	if (t->is_right) {
		PORTB &= ~(1<<t->speed);
		PORTB &= ~(1<<t->forwards);
		PORTB &= ~(1<<t->backwards);
		} else {
		PORTD &= ~(1<<t->speed);
		PORTD &= ~(1<<t->forwards);
		PORTD &= ~(1<<t->backwards);
	}
}

void slide_right(tire* fr, tire* br, tire* fl, tire* bl) {
	move_tire_backwards(fr);
	move_tire_forwards(br);
	move_tire_forwards(fl);
	move_tire_backwards(bl);
}
void turn_right(tire* fr, tire* br, tire* fl, tire* bl);
void spin(tire* fr, tire* br, tire* fl, tire* bl);
void speed_up(tire* fr, tire* br, tire* fl, tire* bl);
void slow_down(tire* fr, tire* br, tire* fl, tire* bl);
void send_item(void);
void stop(tire* fr, tire* br, tire* fl, tire* bl);
