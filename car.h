/*
 * car.h
 *
 * Created: 4/5/2022 2:00:40 PM
 *  Author: mayaguru
 */ 


#ifndef CAR_H_
#define CAR_H_

#include <avr/io.h>

typedef struct tire_tag {
	uint8_t speed;
	uint8_t is_right;
	uint8_t forwards;
	uint8_t backwards;
	} tire;

void init_tire(tire* t, int is_right, uint8_t speed_pin, uint8_t forwards_pin, uint8_t backwards_pin);
void move_tire_backwards(tire* t);
void move_tire_forwards(tire* t);
void stop_tire(tire* t);
void turn_right(tire* fr, tire* br, tire* fl, tire* bl);
void slide_right(tire* fr, tire* br, tire* fl, tire* bl);
void turn_left(tire* fr, tire* br, tire* fl, tire* bl);
void spin(tire* fr, tire* br, tire* fl, tire* bl);
void speed_up(tire* fr, tire* br, tire* fl, tire* bl);
void slow_down(tire* fr, tire* br, tire* fl, tire* bl);
void send_item(void);
void stop(tire* fr, tire* br, tire* fl, tire* bl);




#endif /* CAR_H_ */