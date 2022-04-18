/*
 * car.c
 *
 * Created: 4/5/2022 2:04:18 PM
 *  Author: mayaguru
 */ 
#include "car.h"

void init_dc() {
	dc_fr = 70;
	dc_fl = 70;
	dc_br = 70;
	dc_bl = 70;
}
void init_tire(tire* t, int is_right, uint8_t speed_pin, uint8_t forwards_pin, uint8_t backwards_pin, double dc) {
	t->speed = speed_pin;
	t->is_right = is_right;
	t->forwards = forwards_pin;
	t->backwards = backwards_pin;
	t->dc = dc;
}

void move_tire_forwards(tire* t) {
	if (t->is_right) {
		PORTB |= (1<<t->speed);
		PORTL |= (1<<t->forwards);
		PORTL &= ~(1<<t->backwards);
	} else {
		PORTE |= (1<<t->speed);
		PORTL |= (1<<t->forwards);
		PORTL &= ~(1<<t->backwards);
	}
}

void move_tire_backwards(tire* t) {
	if (t->is_right) {
		PORTB |= (1<<t->speed);
		PORTL &= ~(1<<t->forwards);
		PORTL |= (1<<t->backwards);
		} else {
		PORTE |= (1<<t->speed);
		PORTL &= ~(1<<t->forwards);
		PORTL |= (1<<t->backwards);
	}
}

void move_car_forwards(tire* fr, tire* br, tire* fl, tire* bl) {
	move_tire_forwards(fr);
	move_tire_forwards(fl);
	move_tire_forwards(br);
	move_tire_forwards(bl);
}

void stop_tire(tire* t) {
	if (t->is_right) {
		PORTB &= ~(1<<t->speed);
		PORTL &= ~(1<<t->forwards);
		PORTL &= ~(1<<t->backwards);
		} else {
		PORTE &= ~(1<<t->speed);
		PORTL &= ~(1<<t->forwards);
		PORTL &= ~(1<<t->backwards);
	}
}
void slide_right(tire* fr, tire* br, tire* fl, tire* bl) {
	move_tire_forwards(fr);
	move_tire_backwards(br);
	move_tire_backwards(fl);
	move_tire_forwards(bl);
}

void slide_left(tire* fr, tire* br, tire* fl, tire* bl) {
	move_tire_backwards(fr);
	move_tire_forwards(br);
	move_tire_forwards(fl);
	move_tire_backwards(bl);
}
void turn_right(tire* fr, tire* br, tire* fl, tire* bl) {
	move_tire_backwards(fr);
	move_tire_forwards(bl);
	move_tire_forwards(fl);
	move_tire_backwards(br);
}

void turn_left(tire* fr, tire* br, tire* fl, tire* bl) {
	
	move_tire_forwards(fr);
	move_tire_backwards(bl);
	move_tire_backwards(fl);
	move_tire_forwards(br);
}

void veer_right(tire* fr, tire* br, tire* fl, tire* bl) {
	speed_up_tire(fl);
	speed_up_tire(bl);
	slow_down_tire(fr);
	slow_down_tire(br);
}

void veer_left(tire* fr, tire* br, tire* fl, tire* bl) {
	speed_up_tire(fr);
	speed_up_tire(br);
	slow_down_tire(fl);
	slow_down_tire(bl);
}

void spin(tire* fr, tire* br, tire* fl, tire* bl) {
	turn_right(fr, br, fl, bl);
	_delay_ms(2000);
}

void speed_up_tire(tire* t) {
	if (t->speed == PE3) {
		dc_fl += 20;
	}
	if (t->speed == PB4) {
		dc_fr += 20;
	}
	if (t->speed == PE5) {
		dc_bl += 20;
	}
	if (t->speed == PB5) {
		dc_br += 20;
	}
	
	if (dc_br > 100) {
		dc_br = 100;
	}
	if (dc_bl > 100) {
		dc_bl = 100;
	}
	if (dc_fr > 100) {
		dc_fr = 100;
	}
	if (dc_fl > 100) {
		dc_fl = 100;
	}
	
	
}
void slow_down_tire(tire* t) {
		if (t->speed == PE3 && dc_fl > 20) {
			dc_fl -= 20;
		}
		if (t->speed == PB4 && dc_fr > 20) {
			dc_fr -= 20;
		}
		if (t->speed == PE5 && dc_bl > 20) {
			dc_bl -= 20;
		}
		if (t->speed == PB5 && dc_br > 20) {
			dc_br -= 20;
		}
		
		if (dc_br < 10) {
			dc_br = 10;
		}
		if (dc_bl < 10) {
			dc_bl = 10;
		}
		if (dc_fr < 10) {
			dc_fr = 10;
		}
		if (dc_fl < 10) {
			dc_fl = 10;
		}
		
}
void speed_up(tire* fr, tire* br, tire* fl, tire* bl) {
	speed_up_tire(br);
	speed_up_tire(bl);
	speed_up_tire(fr);
	speed_up_tire(fl);
	
}
void slow_down(tire* fr, tire* br, tire* fl, tire* bl) {
	slow_down_tire(fr);
	slow_down_tire(fl);
	slow_down_tire(br);
	slow_down_tire(bl);
}
void send_item(void);
void stop(tire* fr, tire* br, tire* fl, tire* bl) {
	stop_tire(fr);
	stop_tire(fl);
	stop_tire(br);
	stop_tire(bl);
}