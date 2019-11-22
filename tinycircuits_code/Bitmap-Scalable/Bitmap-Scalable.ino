#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
TinyScreen display = TinyScreen(0);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%% GAME SETUP AND LOOP %%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void setup() {
  Wire.begin();
  display.begin();
  display.setBrightness(15);
  Serial.begin(9600);

  FirstSetup();
}

void loop() {

  Display_Game();
  if (is_clicked(TSButtonUpperRight)){
    AddEXP(1);
  }
}
