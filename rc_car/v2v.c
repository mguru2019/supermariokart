/*
 * v2v.c
 *
 * Created: 4/18/2022 7:01:39 PM
 *  Author: veevinn
 */ 
/*
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <avr/interrupt.h>

#include "v2v.h"

#define dataLen 3  
uint8_t *data;
uint8_t *arr;

void init_wireless_com() {
	DDRB |= (1<<DDB1);  //SCK - Purple
	DDRB |= (1<<DDB2); //MOSI - White
	DDRB |= (1<<DDB3); // MISO - Green
	DDRA |= (1<<DDA0); // CE - Yellow
	DDRA |= (1<<DDA1); // CSN - Orange
	
	SPCR |= (1<<SPE); // Enable SPI
	SPCR |= (1<<MSTR); // Set to MSTR (Clear for Slave)
	
	PORTA |= (1<<PA1); // Set CSN to HIGH, nothing sent yet
	PORTA &= ~(1<<PA0); // Set CE to LOW, nothing to send/recieve yet
}

void transmitData(unsigned char cData) {
	SPDR = cData;	
	while(!(SPSR & (1<<SPIF)));

}

char receiveData(void) {
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

uint8_t nrf_read(uint8_t data) {
	_delay_us(10);
	PORTA &= ~(1<<PA1);
	_delay_us(10);
	transmitData(R_REGISTER + data);
	_delay_us(10);
	data = transmitData(NOP);
	_delay_us(10);
	PORTA |= (1<<PA1);
	return data;	
}

void nrf_write(uint8_t data, uint8_t package) {
	_delay_us(10);
	PORTA &= ~(1<<PA1);
	_delay_us(10);
	transmitData(W_REGISTER + data);
	_delay_us(10);
	data = transmitData(package);
	_delay_us(10);
	PORTA |= (1<<PA1);
}

void nrf24L01_init(void)
{
	_delay_ms(100);	
	
	uint8_t val[5];	

	val[0]=0x01;	
	transmitData(1, EN_AA, val, 1);	
	
	//SETUP_RETR (the setup for "EN_AA")
	val[0]=0x2F;	
	transmitData(1, SETUP_RETR, val, 1);
	
	val[0]=0x01;
	transmitData(W, EN_RXADDR, val, 1); //enable data pipe 0


	val[0]=0x03;
	transmitData(W, SETUP_AW, val, 1); //0b0000 00011 motsvarar 5byte RF_Adress

	//RF channel setup - 
	val[0]=0x01;
	transmitData(W, RF_CH, val, 1); //RF channel registry 0b0000 0001 = 2,401GHz 

	//RF setup	-
	val[0]=0x07;
	transmitData(W, RF_SETUP, val, 1); //00000111 bit 3="0"

	//RX RF_Adress setup 5 byte 
	int i;
	for(i=0; i<5; i++)
	{
		val[i]=0x12;	//RF channel registry 0b10101011 x 5 
	}
	transmitData(W, RX_ADDR_P0, val, 5); //0b0010 1010 write registry 
	//TX RF_Adress setup 5 byte 

	for(i=0; i<5; i++)
	{
		val[i]=0x12;	//RF channel registry 0b10111100 x 5
	}
	transmitData(W, TX_ADDR, val, 5);

	// payload width setup - 
	val[0]=dataLen;		//"0b0000 0001"=1 byte per 5byte RF_Adress  
	transmitData(W, RX_PW_P0, val, 1);
	
	//CONFIG reg setup - 
	val[0]=0x1E;  //0b0000 1110 config registry	bit "1":1=power up,  bit "0":0=transmitter (bit "0":1=Reciver) (bit "4":1=>mask_Max_RT,
	transmitData(W, CONFIG, val, 1);

	//device need 1.5ms to reach standby mode
	_delay_ms(100);

	//sei();
}

*/
