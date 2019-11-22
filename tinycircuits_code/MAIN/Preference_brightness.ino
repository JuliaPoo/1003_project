void draw_brightness_fillbox(int s){
  display.drawRect(18,34, s, 10, TSRectangleFilled, TS_8b_Yellow);
  }

//just a previous arrow
void draw_arrow(){
  display.drawPixel(0,59, TS_8b_Black);
  display.drawPixel(1,58, TS_8b_Black);display.drawPixel(1,59, TS_8b_Black);display.drawPixel(1,60, TS_8b_Black);
  display.drawPixel(2,57, TS_8b_Black);display.drawPixel(2,58, TS_8b_Black);display.drawPixel(2,59, TS_8b_Black);display.drawPixel(2,60, TS_8b_Black);display.drawPixel(2,61, TS_8b_Black);
  display.drawPixel(3,56, TS_8b_Black);display.drawPixel(3,57, TS_8b_Black);display.drawPixel(3,58, TS_8b_Black);display.drawPixel(3,59, TS_8b_Black);display.drawPixel(3,60, TS_8b_Black);display.drawPixel(3,61, TS_8b_Black);display.drawPixel(3,62, TS_8b_Black);
  display.drawPixel(4,55, TS_8b_Black);display.drawPixel(4,56, TS_8b_Black);display.drawPixel(4,57, TS_8b_Black);display.drawPixel(4,58, TS_8b_Black);display.drawPixel(4,59, TS_8b_Black);display.drawPixel(4,60, TS_8b_Black);display.drawPixel(4,61, TS_8b_Black);display.drawPixel(4,62, TS_8b_Black);display.drawPixel(4,63, TS_8b_Black);
  display.setCursor(5,54);
  display.fontColor(TS_8b_Black, TS_8b_White);
  print_header("Previous");
  }  

//draw brightness bar
void drawBBox(){
  display.drawRect(18,34, 60, 10, TSRectangleNoFill, TS_8b_Yellow );
  draw_brightness_fillbox(brightnessCount*4);
  }

//---------------------//
//----BRIGHTNESS------//
//--------------------//

void brightnessLoop(void){
  char * bright_loop = '0';
  display.clearScreen();
  //---------------------//
  //----BASE UI----------//
  //---------------------//
  display.drawRect(0,0,96,64,TSRectangleFilled, TS_8b_White);
  display.drawRect(10,11,76,42,TSRectangleFilled, TS_8b_Gray);
  draw_arrow();
  display.setCursor(24,16);
  print_header("Brightness");
  drawBBox();

  //---------------------------//
  //--------LOOP START HERE----//
  //---------------------------//
  while(bright_loop == '0'){
    if(is_clicked(TSButtonUpperLeft) || is_clicked(TSButtonLowerLeft)){
      break;
      }

    if(is_clicked(TSButtonUpperRight)){
        if(brightnessCount*4 >= 0 && brightnessCount*4 < 60){
          brightnessCount += 1;
          display.clearWindow(18,34,60,10);
          display.drawRect(18,34,60,10, TSRectangleFilled, TS_8b_Gray);
          drawBBox();
          display.setBrightness(brightnessCount);
      }
      }

    if(is_clicked(TSButtonLowerRight)){
      if(brightnessCount*4 > 4 && brightnessCount*4 <= 60){
        brightnessCount -= 1;
        display.clearWindow(18,34,60,10);
        display.drawRect(18,34,60,10, TSRectangleFilled, TS_8b_Gray);
        drawBBox();
        display.setBrightness(brightnessCount);
      }
    }
  }
  }
