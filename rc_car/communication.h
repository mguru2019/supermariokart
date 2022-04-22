/*
 * communication.h
 *
 * Created: 4/21/2022 4:36:26 PM
 *  Author: kasoo
 */ 


#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

//int received_item;

void comm_init();
void ready_to_transmit(void);
void send_item(int item);
void item_sent();
int receive_item_comm(void);


#endif /* COMMUNICATION_H_ */
