// ###########################################
// ####### OPTIONS AT THE START SCREEN #######
// ###########################################

void Setup_Display_Loop(){
  
  display.setCursor(0, 0);
  display.print("New");

  display.setCursor(0, 54);
  display.print("Continue");

  bool is_done = false;
  
  while (!is_done){
    if (is_clicked(TSButtonUpperLeft)) {
      // Confirmation:
      if (reset_confirmation()){
        WriteIsFirst(0); // Set flag to reset EEPROM
        display.clearScreen();
        unsigned char width = display.getPrintWidth("Resetting...");
        display.setCursor(48-(width/2),Ry/2 - 5);
        display.print("Resetting...");
      }
      is_done = true;
    }
    
    if (is_clicked(TSButtonLowerLeft)) {
      WriteIsFirst(1); // Set flag to continue from previous session
      is_done = true;
    }
  }
}

bool reset_confirmation(){
  // Loop that asks user if they wanna reset everything
  
  bool is_done = false;

  display.clearScreen();
  
  unsigned char width = display.getPrintWidth("Reset?");
  display.setCursor(48-(width/2),Ry/2 - 5);
  display.print("Reset?");

  display.setCursor(0, 0);
  display.print("Yes");

  display.setCursor(0, 54);
  display.print("No");

  while (!is_done){
    if (is_clicked(TSButtonUpperLeft)) {
      is_done = true;
      return true;
    }
    if (is_clicked(TSButtonLowerLeft)) {
      is_done = true;
      return false;
    }
  }
}
