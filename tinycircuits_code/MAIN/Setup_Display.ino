// ###########################################
// ####### OPTIONS AT THE START SCREEN #######
// ###########################################

void Setup_Display_Loop(){
  
  display.setCursor(0, 0);
  display.print("New");

  display.setCursor(0, 54);
  display.print("Continue");

  bool is_done = false;
  
  // Requires a loop because this is under Setup and not Loop
  while (!is_done){
    if (display.getButtons(TSButtonUpperLeft)) {
      // Confirmation:
      if (reset_confirmation()){
        WriteIsFirst(0); // Set flag to reset EEPROM
      }
      is_done = true;
      delay(200);
    }
    if (display.getButtons(TSButtonLowerLeft)) {
      WriteIsFirst(1); // Set flag to continue from previous session
      is_done = true;
      delay(200);
    }
  }

  display.clearScreen();
  unsigned char width=display.getPrintWidth("loading...");
  display.setCursor(48-(width/2),Ry/2 - 5);
  display.print("loading...");
}

bool reset_confirmation(){
  bool is_done = false;

  display.clearScreen();
  
  unsigned char width = display.getPrintWidth("Reset everything?");
  Serial.println(width);
  display.setCursor(48-(width/2),Ry/2 - 5);
  display.print("Reset everything?");

  display.setCursor(0, 0);
  display.print("Yes");

  display.setCursor(0, 54);
  display.print("No");

  delay(400);
  while (!is_done){
    if (display.getButtons(TSButtonUpperLeft)) {
      is_done = true;
      delay(200);
      return true;
    }
    if (display.getButtons(TSButtonLowerLeft)) {
      is_done = true;
      delay(200);
      return false;
    }
  }
}
