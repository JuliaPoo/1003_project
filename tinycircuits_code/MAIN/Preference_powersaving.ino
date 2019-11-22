//Print Options
void convert_int_to_str_for_ps(int s){
  char convert[4];
  convert[0] = '\0';
  char output[20];
  output[0]= '\0';
  display.setCursor(15,31);
  display.fontColor(TS_8b_Black, TS_8b_Gray);
  itoa(s, convert, 10);
  strcat(output, convert);
  strcat(output, " Unit");
  display.print(output);
  }



//-------------//
//-POWERSAVING-//
//-------------//

void power_saving_loop(){
  char * power_saving = '0';
  display.clearScreen();

  //------------//
  //--BASE UI---//
  //------------//
  display.drawRect(0,0,95,64, TSRectangleFilled, TS_8b_White);
  display.drawLine(0,10, 96, 10, TS_8b_Black);
  //draw inner rect
  display.drawRect(6,15, 80, 38, TSRectangleFilled, TS_8b_Gray );
  display.setCursor(2,0);
  print_header(options[15]);
  toggle_up_arrow();
  toggle_down_arrow();
  draw_arrow();
  convert_int_to_str_for_ps(*PSPtr);

  //----------------------------//
  //-------LOOP STARTS HERE-----//
  //----------------------------//
  while(power_saving = '0'){
    if(is_clicked(TSButtonUpperRight)){
      if(*PSPtr == 9)
        PSPtr = &PSVal[0];
      else
        PSPtr++;
      display.drawRect(13,20, 40, 20, TSRectangleFilled, TS_8b_Gray );
      convert_int_to_str_for_ps(*PSPtr);
    }
    if(is_clicked(TSButtonLowerRight)){
      if(*PSPtr == 0)
        PSPtr = &PSVal[9];
      else
        PSPtr--;
      display.drawRect(13,20, 40, 20, TSRectangleFilled, TS_8b_Gray );
      convert_int_to_str_for_ps(*PSPtr);
    }
    if(is_clicked(TSButtonLowerLeft)||is_clicked(TSButtonUpperLeft))
      break;
  }
  
  
  }//end
