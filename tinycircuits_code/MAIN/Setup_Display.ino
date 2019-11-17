// ###########################################
// ####### OPTIONS AT THE START SCREEN #######
// ###########################################

bool is_done = false;
void Setup_Display_Loop(){

  display.fontColor(TS_8b_White,TS_8b_Black);
  display.setFont(thinPixel7_10ptFontInfo);
  
  display.setCursor(0, 0);
  display.print("New");

  display.setCursor(0, 54);
  display.print("Continue");
  
  while (!is_done){
    if (display.getButtons(TSButtonUpperLeft)) {
      WriteIsFirst(0);
      is_done = true;
      delay(200);
    }
    if (display.getButtons(TSButtonLowerLeft)) {
      WriteIsFirst(1);
      is_done = true;
      delay(200);
    }
  }

  display.clearScreen();
}
