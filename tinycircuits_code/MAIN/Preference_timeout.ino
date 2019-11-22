//Just an arrow
void toggle_up_arrow(){
  unsigned char i, k;
  for (k = 55; k <= 62; ++k){
    for(i = k; i< 71+55-k; i++){
      display.drawPixel(i,33 + 55 - k, TS_8b_Black);
    }
  }
}

//Just an arrow
void toggle_down_arrow(){
  unsigned char i, k;
  for (k = 55; k <= 62; k++){
    for (i = k; i < 71+55-k; i++){
      display.drawPixel(i, 38-55+k, TS_8b_Black);
    }
  }
}

//Print options
void convert_int_to_str(int s){
  char convert[4];
  convert[0] = '\0';
  char output[8];
  output[0]= '\0';
  display.setCursor(15,31);
  display.fontColor(TS_8b_Black, TS_8b_Gray);
  if(*timeOutPtr == 1 || *timeOutPtr == 2){
    itoa(s*15, convert, 10);
    strcat(output, convert);
    strcat(output, " Sec");
    display.print(output);
    }
    else{
      int x = s / 4;
      itoa(x, convert, 10);
      strcat(output, convert);
      strcat(output, " Min");
      display.print(output);
      }
  }


//-------------------//
//----TIME OUT------//
//-----------------//
void timeout_loop(){
  char * timeout = '0';
  display.clearScreen();
  //Drawing UI for TimeOutLoop
  display.drawRect(0,0,95,64, TSRectangleFilled, TS_8b_White);
  cross_button();
  display.drawLine(0,10, 96, 10, TS_8b_Black);
  //draw inner rect
  display.drawRect(6,15, 80, 38, TSRectangleFilled, TS_8b_Gray );
  display.setCursor(2,0);
  print_header(*optionsPtr);
  toggle_up_arrow();
  toggle_down_arrow();
  draw_arrow();
  convert_int_to_str(*timeOutPtr);


  //Loop Starts Here
  while(timeout = '0'){
    if(is_clicked(TSButtonUpperRight)){
      if(*timeOutPtr == 20)
        timeOutPtr = &T_O_Value[0];
      else
        timeOutPtr++;
      display.drawRect(13,20, 40, 20, TSRectangleFilled, TS_8b_Gray );
      convert_int_to_str(*timeOutPtr);
    }
    if(is_clicked(TSButtonLowerRight)){
      if(*timeOutPtr == 1)
        timeOutPtr = &T_O_Value[5];
      else
        timeOutPtr--;
      display.drawRect(13,20, 40, 20, TSRectangleFilled, TS_8b_Gray );
      convert_int_to_str(*timeOutPtr);
    }
    if(is_clicked(TSButtonLowerLeft)||is_clicked(TSButtonUpperLeft))
      break;
  }
  
  
  }//end
