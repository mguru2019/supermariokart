
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(6,7);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

// Used to control whether this node is sending or receiving
bool role = 0;

void setup() {

  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

    // Set the speed of the transmission to the quickest available
  radio.setDataRate(RF24_2MBPS);

  // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setChannel(124);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }else{
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  
  
/****************** Ping Out Role ***************************/  
  if (role == 1)  {
    
    radio.stopListening();                                    // First, stop listening so we can talk
    Serial.println(F("Now sending"));
  
    unsigned int data = 1;
    unsigned long start_time = micros();            
    
   /* if (digitalRead(8) == HIGH && digitalRead(9) == LOW && digitalRead(10) == LOW) { // BULLET
      data = 1;
    }
    else if (digitalRead(8) == LOW && digitalRead(9) == HIGH && digitalRead(10) == LOW) { // REDSHELL
      data = 2;
    }
    else if (digitalRead(8) == LOW && digitalRead(9) == LOW && digitalRead(10) == HIGH) { // GREENSHELL
      data = 3;
    }
    else if (digitalRead(8) == HIGH && digitalRead(9) == HIGH && digitalRead(10) == LOW) { // LIGHTNING
      data = 4;
    }
    else if (digitalRead(8) == HIGH && digitalRead(9) == LOW && digitalRead(10) == HIGH) { // POW
      data = 5;
    }
    else if (digitalRead(8) == LOW && digitalRead(9) == HIGH && digitalRead(10) == HIGH) { // BLUESHELL
      data = 6;
    }
    else {
      data = 0;
    } */
     if (!radio.write( &data, sizeof(unsigned int) )){
       Serial.println(F("failed"));
     }
        
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }
        
    if ( timeout ){                                             // Describe the results
        Serial.println(F("Failed, response timed out."));
    }else{
     
        unsigned int got_data;
        radio.read( &got_data, sizeof(unsigned int) );
       // role = 0;
        
        // Spew it
        Serial.print(F("Sent "));
        Serial.print(data);
        Serial.print(F(", Got response "));
        Serial.print(got_data);
    }

    // Try again 1s later
    delay(1000);
  }



/****************** Pong Back Role ***************************/

  if ( role == 0 )
  {
    if (digitalRead(8) == HIGH && digitalRead(9) == HIGH && digitalRead(10) == HIGH) {
    role = 1;
   }
   
    unsigned long got_time;
    unsigned int got_data;
    
    if( radio.available()){
                                                                    // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &got_data, sizeof(unsigned int) );             // Get the payload
      }
     
      radio.stopListening();                                        // First, stop listening so we can talk   
      radio.write( &got_data, sizeof(unsigned int) );              // Send the final one back.      
      radio.startListening();                                       // Now, resume listening so we catch the next packets.     
      Serial.print(F("Sent response "));
      Serial.println(got_data);  
   }
   
   
  /* if (got_data == 1) { // BULLET
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
   }
   else if (got_data == 2) { // REDSHELL
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
   }
   else if (got_data == 3) { // GREENSHELL
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
   }
   else if (got_data == 4) { // LIGHTNING
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
   }
   else if (got_data == 5) { // POW
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
   }
   else if (got_data == 6) { // BLUESHELL
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
   }
   else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
   }*/
 }




/****************** Change Roles via Serial Commands ***************************/

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == 0 ){      
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      role = 1;                  // Become the primary transmitter (ping out)
    
   }else
    if ( c == 'R' && role == 1 ){
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));      
       role = 0;                // Become the primary receiver (pong back)
       radio.startListening();
       
    }
  }


} // Loop

    // Set the speed of the transmission to the quickest available
  radio.setDataRate(RF24_2MBPS);

  // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setChannel(124);
