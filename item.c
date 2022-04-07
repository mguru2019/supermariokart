/*
 * item.c
 *
 * Created: 4/6/2022 2:39:48 PM
 *  Author: mayaguru
 */ 

#include "item.h"

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
	has_item = 0;
}
