/*
 * character.c
 *
 * Created: 4/13/2022 10:56:11 AM
 *  Author: veevinn
 */ 
#include "character.h"
#include "LED.h"

void choose_character() {
	
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
		green=102; // GREEN
		blue=255; // BLUE
	}
	
	else if (character == BOWSER) { //ORANGE
		red=255; // RED
		green=165; // GREEN
		blue=0; // BLUE
	}
	
	else if (character == YOSHI) { //LIGHT GREEN
		red=244; // RED
		green=238; // GREEN
		blue=144; // BLUE
	}
	
	else if (character == DAISY) { //LIGHT PURPLE
		red=203; // RED
		green=195; // GREEN
		blue=227; // BLUE
	}
	
	else if (character == TOAD) { //BLUE
		red=0; // RED
		green=0; // GREEN
		blue=255; // BLUE
	}
	
	else if (character == DONKEYKONG) { //BROWN
		red=150; // RED
		green=75; // GREEN
		blue=0; // BLUE
	}
		
	pwm(0,red);
	pwm(1,green);
	pwm(2,blue);
}
