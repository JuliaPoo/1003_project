#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
TinyScreen display = TinyScreen(0);

void setup (){
  // Setup EEPROM
  Setup_EEPROM();

  // Setup hardware
  Wire.begin();
  Serial.begin(9600);
  display.begin();
  display.setBrightness(GetPreferences(0));
}


void loop(){
}
