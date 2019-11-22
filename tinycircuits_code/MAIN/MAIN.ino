#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Time.h>
#include "const.h"

TinyScreen display = TinyScreen(0);

long UseTime;

void setup(){
  
  // Setup hardware
  Wire.begin();
  Serial.begin(9600);
  display.begin();

  // Set font
  display.fontColor(TS_8b_White, TS_8b_Black);
  display.setFont(thinPixel7_10ptFontInfo);

  // Setup EEPROM
  Setup_Display_Loop(); // Asks user if they want to start a new game or continue from their previous session
  Setup_EEPROM();
  display.setBrightness(GetPreferences(0));

  UseTime = millis();
}


void loop(){

  // Checks to enter menu loop
  // An if else for the game screen for performance of gamescreen
  // There is already NO delay used in game screen yet it is still so laggy due to the other functions
  
  if (is_clicked(TSButtonUpperLeft)){
    Menu_Loop();
  } 

  Display_Game();
  if (is_clicked(TSButtonUpperRight)){
    AddEXP(1);
  }
  
  if (millis() - UseTime > TIMEOUT) Idle_Loop(&UseTime);

  if (is_any_button()){
    UseTime = millis();
  }

  //If ever wanna for performance
  delay(POWER_SAVING_LEVEL * 10);
}
