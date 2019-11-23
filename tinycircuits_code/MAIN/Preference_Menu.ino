//Preferences Options
#define N_OPTIONS 3
char * options[16] = {"Set Brightness", "Set Timeout", "Power Saving"};
char ** optionsPtr = options;

//use to toggle brightnessBox -> brightness bar and set brightnessCount -> setBrightness() @ brightnessLoop.ino
//Take the value of brightnessCount
unsigned char brightnessCount;

//Time_Out Value Options, Just take pointer value (in 15*n Seconds)
unsigned char T_O_Value[6] = {1, 2, 4, 8, 20, 60}; 
unsigned char *timeOutPtr;

//Powersaving values
unsigned char PSVal[10]={0,1,2,3,4,5,6,7,8,9};
unsigned char *PSPtr = &PSVal[0];


void print_header(char* s){
  display.setFont(thinPixel7_10ptFontInfo);
  display.fontColor(TS_8b_Black, TS_8b_White);
  display.print(s);
}

//Set all available options for Settings
void set_options()
{
//calculate length of options
  int optionLength = sizeof(options)/ sizeof(options[0]);
  int xaxis, yaxis = 17;
  display.setFont(thinPixel7_10ptFontInfo);
  display.fontColor(TS_8b_Black, TS_8b_Gray);
  for(int i = 0; i< optionLength; i ++)
  {
    xaxis = 96/2 - display.getPrintWidth(options[i])/2 - 1;
    display.setCursor(xaxis,yaxis);
    display.print(options[i]);
    yaxis += 10;
  }
}
//Yellow highlight options
void update_selector(){
  if(*optionsPtr == "Set Brightness")
  {
    display.clearWindow(13-1,17, 71-1, 10);
    display.setCursor(13-1,17);
    display.fontColor(TS_8b_Black, TS_8b_Yellow);
    display.print(options[0]);
  }
  else if(*optionsPtr == "Set Timeout"){
    display.clearWindow(20-1,27, 57-1, 10);
    display.setCursor(20-1,27);
    display.fontColor(TS_8b_Black, TS_8b_Yellow);
    display.print(options[1]);
  }
  else if (*optionsPtr == "Power Saving"){
    display.clearWindow(17-1,37, 62-1, 10);
    display.setCursor(17-1,37);
    display.fontColor(TS_8b_Black, TS_8b_Yellow);
    display.print(options[2]);
  }
}

//draw Base UI
void drawSettingsMenu(){
  display.drawRect(0, 0, 95, 64, TSRectangleFilled, TS_8b_White);
  display.setCursor(25,0);
  print_header("Settings");
  out_box();
  //draw line
  display.drawLine(0,10, 96, 10, TS_8b_Black);
  //draw inner rect
  display.drawRect(6,15, 84, 44, TSRectangleFilled, TS_8b_Gray);
  set_options();
  update_selector();
  }


void GetEEPROMPref(){
  brightnessCount = GetPreferences(0);
  unsigned char timeout = GetPreferences(1);
  unsigned char power_saving = GetPreferences(2);
  
  for (timeOutPtr = T_O_Value; timeOutPtr <= T_O_Value + 6; timeOutPtr ++){
    if (timeout == *timeOutPtr) break;
    if (timeOutPtr == T_O_Value + 6){
      timeOutPtr = &T_O_Value[1];
      break;
    }
  }  
  
  for (PSPtr = PSVal; PSPtr <= PSVal + 10; PSPtr ++){
    if (power_saving == *PSPtr) break;
    if (PSPtr == PSVal + 10){
      PSPtr = &PSVal[0];
      break;
    }
  }
}


void Preference_Menu_Loop(void){
  char UI_loop = '0';
  drawSettingsMenu();
  GetEEPROMPref();

  //Loop Starts Here
  while(UI_loop == '0')
  {
  //------------------------//
  //------TOGGLE OPTIONS----//
  //------------------------// 
    if(is_clicked(TSButtonUpperLeft))
    {
      if(*optionsPtr == "Set Brightness"){
        optionsPtr = &options[2];
      }
      else{
        optionsPtr = (optionsPtr - options - 1)%N_OPTIONS + options;}
      set_options();
      update_selector();
    }

    if(is_clicked(TSButtonLowerLeft))
    {
      if(*optionsPtr == "Power Saving"){
        optionsPtr = &options[0];  
      }
      else{
        optionsPtr = (optionsPtr - options + 1)%N_OPTIONS + options;}
      set_options();
      update_selector();
    }

  //------------------------//
  //------SELECT OPTIONS----//
  //------------------------//
  
    if(is_clicked(TSButtonLowerRight))
    {
      if(*optionsPtr == "Set Brightness"){
        brightnessLoop();
        display.clearScreen();
        drawSettingsMenu();
        WritePreferences(brightnessCount, 0);
        //Serial.println(brightnessCount);
      }
      else if (*optionsPtr == "Set Timeout"){
        timeout_loop();
        display.clearScreen();
        drawSettingsMenu();
        WritePreferences(*timeOutPtr, 1);
        //Serial.println(*timeOutPtr * 15);
      }
      else if (*optionsPtr == "Power Saving"){
        power_saving_loop();
        display.clearScreen();
        drawSettingsMenu();
        WritePreferences(*PSPtr, 2);
        //Serial.println(*PSPtr);
      }
    }

  //------------------------//
  //-----EXIT PREFERENCE----//
  //------------------------//

      if (is_clicked(TSButtonUpperRight)){
        UI_loop = '1';
      }
  
  } 

}
