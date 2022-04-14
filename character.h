/*
 * character.h
 *
 * Created: 4/13/2022 10:56:28 AM
 *  Author: veevinn
 */ 


#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "car.h"

#define MARIO 1
#define LUIGI 2
#define WALUIGI 3
#define WARIO 4
#define PEACH 5
#define BOWSER 6
#define YOSHI 7
#define DAISY 8
#define TOAD 9
#define DONKEYKONG 10

int game_state;
int selected_character;
int user_character;

void init_state();
void light_led(int character);
void choose_character();
void character_locked(tire* fr, tire* br, tire* fl, tire* bl);





#endif /* CHARACTER_H_ */
