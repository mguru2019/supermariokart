/*
 * item.h
 *
 * Created: 4/6/2022 2:39:38 PM
 *  Author: mayaguru
 */ 


#ifndef ITEM_H_
#define ITEM_H_

#include <stdlib.h>
#include "car.h"
#include "LED.h"
#include "character.h"

#define MUSHROOM 1
#define STAR 2
#define BANANA 3
#define BULLET 4
#define REDSHELL 5
#define GREENSHELL 6
#define LIGHTNING 7
#define POW 8
#define BLUESHELL 9

double dc_item;
int has_item;
int item;

int choose_item(void);
void deploy_item(int item, tire* fr, tire* br, tire* fl, tire* bl);










#endif /* ITEM_H_ */