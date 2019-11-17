#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"

TinyScreen display = TinyScreen(0);
unsigned char PAUSE_GAME = 0; // set to 1 to pause game screen

void setup (){
  
  // Setup hardware
  Wire.begin();
  Serial.begin(9600);
  display.begin();

  // Set font
  display.fontColor(TS_8b_White,TS_8b_Black);
  display.setFont(thinPixel7_10ptFontInfo);

  // Setup EEPROM
  Setup_Display_Loop(); // Asks user if they want to start a new game or continue from their previous session
  Setup_EEPROM();
  display.setBrightness(GetPreferences(0));
  
}


void loop(){

  // Draws game screen including the hamburger menu (avoid flickering at the expense of messy code)
  if (!PAUSE_GAME){
    Display_Game_Screen();
  }

  // Checks to enter menu loop
  if (is_clicked(TSButtonUpperLeft)){
    /*
    delay(200);
    PAUSE_GAME = true;
    //Menu_Loop();
    PAUSE_GAME = false;
    */
    Serial.println("is clicked");
  }
  
  delay(50); // Whole app loop will have max fps=20
}
