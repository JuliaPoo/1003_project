#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Time.h>
#include "const.h"

#define TIMEOUT 30000 // Displays idle screen after 30s Only takes effect while in the game screen

TinyScreen display = TinyScreen(0);
long UseTime; // For Screen Saver

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

  // Draws game screen including the hamburger menu (avoid flickering at the expense of messy code)
  Display_Game_Screen();

  // Checks to enter menu loop
  if (is_clicked(TSButtonUpperLeft)){
    Menu_Loop();
  }

  if (millis() - UseTime > TIMEOUT) Idle_Loop(&UseTime);

  if (is_any_button()){
    UseTime = millis();
  }
  
  delay(50); // Whole app loop will have max fps=20
}
