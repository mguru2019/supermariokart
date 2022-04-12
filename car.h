/*
 * car.h
 *
 * Created: 4/5/2022 2:00:40 PM
 *  Author: mayaguru
 */ 


#ifndef CAR_H_
#define CAR_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


double dc_fr;
double dc_fl;
double dc_br;
double dc_bl;

typedef struct tire_tag {
	uint8_t speed;
	uint8_t is_right;
	uint8_t forwards;
	uint8_t backwards;
	int dc;
	} tire;

void init_dc();
void init_tire(tire* t, int is_right, uint8_t speed_pin, uint8_t forwards_pin, uint8_t backwards_pin, double dc);
void move_tire_backwards(tire* t);
void move_tire_forwards(tire* t);
void move_car_forwards(tire* fr, tire* br, tire* fl, tire* bl);
void stop_tire(tire* t);
void slide_right(tire* fr, tire* br, tire* fl, tire* bl);
void turn_right(tire* fr, tire* br, tire* fl, tire* bl);
void veer_right(tire* fr, tire* br, tire* fl, tire* bl);
void slide_left(tire* fr, tire* br, tire* fl, tire* bl);
void turn_left(tire* fr, tire* br, tire* fl, tire* bl);
void veer_left(tire* fr, tire* br, tire* fl, tire* bl);
void spin(tire* fr, tire* br, tire* fl, tire* bl);
void speed_up_tire(tire* t);
void slow_down_tire(tire* t);
void speed_up(tire* fr, tire* br, tire* fl, tire* bl);
void slow_down(tire* fr, tire* br, tire* fl, tire* bl);
void send_item(void);
void stop(tire* fr, tire* br, tire* fl, tire* bl);




#endif /* CAR_H_ */