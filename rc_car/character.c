/*
 * character.c
 *
 * Created: 4/13/2022 10:56:11 AM
 *  Author: veevinn
 */ 
#include "character.h"
#include "LED.h"

void init_state() {
	game_state = 0;
	user_character = 0;
	selected_character = 0;
	DDRA &= ~(1<<DDA6);
}

void light_led(int character) {
	init_led();
	int red = 0;
	int green = 0;
	int blue = 0;
	
	if (character == MARIO) { //RED
		red=255; // RED
		green=0; // GREEN
		blue=0; // BLUE
	}
	
	else if (character == LUIGI) { //GREEN
		red=0; // RED
		green=255; // GREEN
		blue=0; // BLUE
	}
	
	else if (character == WALUIGI) { //PURPLE
		red=149; // RED
		green=0; // GREEN
		blue=179; // BLUE
	}
	
	else if (character == WARIO) { //YELLOW
		red=255; // RED
		green=255; // GREEN
		blue=0; // BLUE
	}
	
	else if (character == PEACH) { //PINK
		red=255; // RED
		green=0; // GREEN
		blue=107; // BLUE
	}
	
	else if (character == BOWSER) { //ORANGE
		red=255; // RED
		green=51; // GREEN
		blue=0; // BLUE
	}
	
	else if (character == YOSHI) { //LIGHT GREEN
		red=102; // RED
		green=204; // GREEN
		blue=0; // BLUE
	}
	
	else if (character == DAISY) { //LIGHT PURPLE
		red=204; // RED
		green=153; // GREEN
		blue=255; // BLUE
	}
	
	else if (character == TOAD) { //BLUE
		red=0; // RED
		green=0; // GREEN
		blue=255; // BLUE
	}
	
	else if (character == DONKEYKONG) { //BROWN
		red=102; // RED
		green=51; // GREEN
		blue=0; // BLUE
	}
	
	pwm(0,red);
	pwm(1,green);
	pwm(2,blue);
}

void choose_character() {
	if (game_state == 0) {		
		if (PINF & (1<<PINF2) && PINF & (1<<PINF3) && ~(PINF & (1<<PINF4)) && ~(PINF & (1<<PINF5))) {
			selected_character = DONKEYKONG;
		}
		else if ((PINF & (1<<PINF2)) && ~(PINF & (1<<PINF3)) && ~(PINF & (1<<PINF4)) && (PINF & (1<<PINF5))) {
			selected_character = TOAD;
		}
		else if (~(PINF & (1<<PINF2)) && (PINF & (1<<PINF3)) && ~(PINF & (1<<PINF4)) && (PINF & (1<<PINF5))) {
			selected_character = DAISY;
		}
		else if ((PINF & (1<<PINF2)) && ~(PINF & (1<<PINF3)) && (PINF & (1<<PINF4)) && ~(PINF & (1<<PINF5))) {
			selected_character = YOSHI;
		}
		else if (~(PINF & (1<<PINF2)) && (PINF & (1<<PINF3)) && (PINF & (1<<PINF4)) && ~(PINF & (1<<PINF5))) {
			selected_character = BOWSER;
		}
		else if (~(PINF & (1<<PINF2)) && ~(PINF & (1<<PINF3)) && (PINF & (1<<PINF4)) && (PINF & (1<<PINF5))) {
			selected_character = PEACH;
		}
		else if ((PINF & (1<<PINF2)) && ~(PINF & (1<<PINF3)) && ~(PINF & (1<<PINF4)) && ~(PINF & (1<<PINF5))) {
			selected_character = WARIO;
		}
		else if (~(PINF & (1<<PINF2)) && (PINF & (1<<PINF3)) && ~(PINF & (1<<PINF4)) && ~(PINF & (1<<PINF5))) {
			selected_character = WALUIGI;
		}
		else if (~(PINF & (1<<PINF2)) && ~(PINF & (1<<PINF3)) && ~(PINF & (1<<PINF4)) && (PINF & (1<<PINF5))) {
			selected_character = LUIGI;
		}
		else if (~(PINF & (1<<PINF2)) && ~(PINF & (1<<PINF3)) && (PINF & (1<<PINF4)) && ~(PINF & (1<<PINF5))) {
			selected_character = MARIO;
		}
		else if ((PINF & (1<<PINF2)) && (PINF & (1<<PINF3)) && (PINF & (1<<PINF4)) && (PINF & (1<<PINF5))){
			selected_character = rand() % 10 + 1;
		}
		else {
			selected_character = 0;
			led_off();
		}
	}
}

void character_locked(tire* fr, tire* br, tire* fl, tire* bl) {
	if (PINA & (1<<PINA6)) {		
		user_character = selected_character;
		game_state = 1;
	}
}

