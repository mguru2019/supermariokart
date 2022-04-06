/*
 * item.c
 *
 * Created: 4/6/2022 2:39:48 PM
 *  Author: mayaguru
 */ 

#include "item.h"

int choose_item(int adc) {
	//case on adc value
	/*
	if (!has_item) {
		int item = rand() % 9 + 1;
		has_item = 1;
		return item;
	}
	return 0;
	*/
	
	int item = rand() % 9 + 1;
	has_item = 1;
	return item;
}
