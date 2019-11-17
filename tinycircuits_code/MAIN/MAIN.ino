#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"

TinyScreen display = TinyScreen(0);


void setup (){
  
  // Setup hardware
  Wire.begin();
  Serial.begin(9600);
  display.begin();

  // Setup EEPROM
  Setup_Display_Loop(); // Asks user if they want to start a new game or continue from their previous session
  Setup_EEPROM();
  display.setBrightness(GetPreferences(0));
  
}


void loop(){
}
