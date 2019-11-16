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

  Serial.println(GetPreferences(0)); // Prints brightness
  Serial.println(GetPreferences(1)); // Prints some_other_variable

  char OUT[LEN_TODO+1];
  GetTodo(OUT, 0);
  Serial.println(OUT);  // Prints todo list at index 0
  GetTodo(OUT, 1);
  Serial.println(OUT);  // Prints todo list at index 1

  Serial.println(GetGameVariables(0));  // Prints EXP
  Serial.println(GetGameVariables(1));  // Prints LEVEL
}

void loop(){
}
