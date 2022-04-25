/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.
    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app
  Blynk library is licensed under MIT license
  This example code is in public domain.
 *************************************************************
  This example runs directly on NodeMCU.
  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino
  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!
  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino
  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/**
 * FILL OUT THE FOLLOWING BASED ON YOUR TEMPLATE INFORMATION
 * 1. BLYNK_TEMPLATE_ID (line 48)
 * 2. BLYNK_DEVICE_NAME (line 49)
 * 3. BLYNK_AUTH_TOKEN (line 50)
 */

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLdYt0eL8U"
#define BLYNK_DEVICE_NAME "SuperMarioKart"
#define BLYNK_AUTH_TOKEN "1YGVSUw_mIN6HM4NWR7IiQoafUs2g6Yb"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <stdio.h>
//#include <SimpleTimer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AirPennNet-Device";
char pass[] = "penn1740wifi";

int game_state = 0;

//SimpleTimer timer;
int val = 0;

int high_total = 0;
int total = 0;
int start_seq = 0;
int wave_counter = 0;

char item[25];
char item_label[6] = "Item:";
int starting_place = 0;

WidgetLCD lcd(V15);

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

BLYNK_WRITE(V2) { // Mario
    if (param.asInt() == 1 && game_state == 0) {
      digitalWrite(D0, HIGH);
    }
    else {
      digitalWrite(D0, LOW);
    }
}

BLYNK_WRITE(V3) { // Luigi
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D1, HIGH);
  }
  else {
    digitalWrite(D1, LOW);
  }
}

BLYNK_WRITE(V4) { // Waluigi
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D2, HIGH);
  }
  else {
    digitalWrite(D2, LOW);
  }
}

BLYNK_WRITE(V5) { // Wario
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D3, HIGH);
  }
  
  else {
    digitalWrite(D3, LOW);
  }
}

BLYNK_WRITE(V6) { // Peach
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D0, HIGH);
    digitalWrite(D1, HIGH);
  }
  else {
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
  }
}

BLYNK_WRITE(V7) { // Bowswer
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D0, HIGH);
    digitalWrite(D2, HIGH);
  }
  else {
    digitalWrite(D0, LOW);
    digitalWrite(D2, LOW);  
    }
}

BLYNK_WRITE(V8) { // Yoshi
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D0, HIGH);
    digitalWrite(D3, HIGH);

  }
  else {
    digitalWrite(D0, LOW);
    digitalWrite(D3, LOW);
  }
}

BLYNK_WRITE(V9) { // Daisy
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
  } 
  else {
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
  } 
}

BLYNK_WRITE(V10) { // Toad
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D1, HIGH);
    digitalWrite(D3, HIGH);
  }
  
  else {
    digitalWrite(D1, LOW);
    digitalWrite(D3, LOW);
  }
  
}

BLYNK_WRITE(V11) { // Donkey Kong
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
  }
  
  else {
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
  }
  
}

BLYNK_WRITE(V12) { // Random
  if (param.asInt() == 1 && game_state == 0) {
    digitalWrite(D0, HIGH);
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
  }
  
  else {
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
  }
  
}

BLYNK_WRITE(V13) {
  if (param.asInt() == 1 && game_state == 0) {
   digitalWrite(D5, HIGH);
   digitalWrite(D0, LOW);
   digitalWrite(D1, LOW);
   digitalWrite(D2, LOW);
   digitalWrite(D3, LOW);
   game_state = 1;
  }
  else {
  digitalWrite(D5, LOW);
  game_state = 0;
  }
}

BLYNK_WRITE(V0) {
  int x = param[0].asInt();
  int y = param[1].asInt();
  if (x <= 75 && game_state == 1) {
    Serial.println("Got Here");
    digitalWrite(D0, HIGH);
    digitalWrite(D1,LOW);
  }
  else if (x >= 175 && game_state == 1) {
    digitalWrite(D1, HIGH);
    digitalWrite(D0,LOW);
  }
  else {
    digitalWrite(D1, LOW);
    digitalWrite(D0,LOW);
  }

  if (y >= 150 && game_state == 1) {
    digitalWrite(D2, HIGH);
  }
  else {
    digitalWrite(D2, LOW);
  }
}

BLYNK_WRITE(V1) {
  
  if (param.asInt() == 1 && game_state == 1) {
    digitalWrite(D3, HIGH);
  }
  else {
    digitalWrite(D3, LOW);
  }
}
BLYNK_WRITE(V14) {
  if(param.asInt() == 1 && game_state == 1) {
    digitalWrite(D6, HIGH);
    lcd.clear();
    sprintf(item, "");
    high_total = 0;
    start_seq = 0;
    total = 0;
    wave_counter = 0;
  }
  else {
    digitalWrite(D6, LOW);
  }
}

void item_display() {
  //Serial.println(total);
   Serial.println(high_total);
 // lcd.print(7, 0, item_label);
   
   if (val==1024 && start_seq == 0) {
    start_seq = 1;
    total = 0;
   }
   if (start_seq == 1) {
    total++;
    if (val == 1024) {
      high_total++;
      }
    if (total == 99 && wave_counter == 0) {
      wave_counter++;
      high_total = 0;
      total = 0;
      lcd.clear();
    }
     
    if (total == 99 && wave_counter > 0) {    
      if (high_total >= 95 && high_total <= 100) {
        //Serial.println("Banana");
        sprintf(item, "Blue Shell");
        starting_place = 4;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 85 && high_total < 95) {
        //Serial.println("Banana");
        sprintf(item, "Pow");
        starting_place = 4;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 75 && high_total < 85) {
        //Serial.println("Banana");
        sprintf(item, "Lightning");
        starting_place = 4;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 65 && high_total < 75) {
        //Serial.println("Banana");
        sprintf(item, "Green Shell");
        starting_place = 4;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 55 && high_total < 65) {
        //Serial.println("Banana");
        sprintf(item, "Red Shell");
        starting_place = 4;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 45 && high_total < 55) {
        //Serial.println("Banana");
        sprintf(item, "Bullet");
        starting_place = 4;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 35 && high_total < 45) {
        //Serial.println("Banana");
        sprintf(item, "Banana");
        starting_place = 4;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 25 && high_total < 35) {
        //Serial.println("Star");
        sprintf(item, "Star");
        starting_place = 5;
        lcd.print(starting_place, 0, item); 
      }
      if (high_total >= 15 && high_total < 25) {
        sprintf(item, "Mushroom");
        starting_place = 3;
        lcd.print(starting_place, 0, item); 
      }    
      total = 0;
      high_total = 0;  
    }
    else {
      sprintf(item, "");
      starting_place = 1;
      lcd.print(starting_place, 0, item);  
    }
    
   }
  
 // Blynk.virtualWrite(V15, "Mushroom")
} 

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  val = analogRead(A0);
 // total++;
  Blynk.run();
  //Serial.println(val);
  item_display();
  //if(val == 1024) {
   // high_total++;
  //}
}
