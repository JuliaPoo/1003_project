// ########################
// ####### MENU BAR #######
// ########################

#define N_OPTIONS 4               // Number of options on the menu

#define BACKGROUND 219            // Background colour of unselected item
#define SELECTED_BACKGROUND 182   // Background colour of selected item
#define SHADOW 111                // Shadow of menu

// Set display params
#define rec_h 10                  // Height of each option
#define rec_w 66                  // Width of each option
#define left_pad 3                // padding left of text
#define menu_left_pad 5           // padding left of menu
#define menu_top_pad 5            // padding top of menu

void Menu_Loop(){
  unsigned char is_done = false;

  // Initialise cursor
  unsigned char y = 0;
  display.fontColor(TS_8b_Black, BACKGROUND);
  display.drawRect(menu_left_pad + 2,
                   menu_top_pad + 2,
                   rec_w, 
                   rec_h * N_OPTIONS, 
                   1, 
                   SHADOW); // Draws shadow cuz it looks awesome

  Draw_Menu(y);
  while (!is_done){
    
    // Moving cursor
    if (is_clicked(TSButtonUpperLeft)){
      y = (N_OPTIONS + y - 1) % N_OPTIONS; // Essentially y = (y-1) % N_OPTIONS but y is always positive
      Draw_Menu(y);
    }
    if (is_clicked(TSButtonLowerLeft)){
      y = (y + 1) % N_OPTIONS;
      Draw_Menu(y);
    }

    // Selecting option
    if (is_clicked(TSButtonLowerRight)){
      ExecuteOption(y);
      is_done = true;
    }
  }
  
  // Change font back
  display.fontColor(TS_8b_White, TS_8b_Black);
}

void Draw_Menu(unsigned char y){

  // If need be, can be more memory efficient at the expense of cancer
  // UPDATE: Had to remove "Achievements" because of memory :( Am sad.
  char MenuOptions[N_OPTIONS][16] = {"To Do List", "Preferences", "Reset", "Back"};
  
  unsigned char i;
  char option[15];
  for (i = 0; i < N_OPTIONS; ++i){

    strcpy(option, MenuOptions[i % N_OPTIONS]);
    
    if (i == y % N_OPTIONS){
      display.fontColor(TS_8b_Black, SELECTED_BACKGROUND);
      
      display.drawRect(menu_left_pad,
                       rec_h*i + menu_top_pad,
                       rec_w, 
                       rec_h, 
                       1, 
                       SELECTED_BACKGROUND);
                       
      display.setCursor(menu_left_pad + left_pad, menu_top_pad + rec_h*i);
      display.print(option);
      display.fontColor(TS_8b_Black, BACKGROUND);
    } else {
      display.drawRect(menu_left_pad,
                       rec_h*i + menu_top_pad,
                       rec_w, 
                       rec_h, 
                       1, 
                       BACKGROUND);
                       
      display.setCursor(menu_left_pad + left_pad, menu_top_pad + rec_h*i);
      display.print(option);
    }
  }
}

void ExecuteOption(unsigned char y){
  if (y == 0) ToDoList_Loop();
  else if (y == 1) Preference_Loop();
  else if (y == 2) Achievements_Loop();
  else if (y == 3) Reset_Loop();
  else if (y == 4) Back();
}

void ToDoList_Loop(){
  UI_Todo_Loop(); // Launched To-do list
}

void Preference_Loop(){
  Preference_Menu_Loop();
}

void Achievements_Loop(){}

void Reset_Loop(){
  display.fontColor(TS_8b_White, TS_8b_Black);
  if (reset_confirmation()){
    WriteIsFirst(0); // Set flag to reset EEPROM
    display.clearScreen();
    unsigned char width = display.getPrintWidth("Resetting...");
    display.setCursor(48-(width/2),Ry/2 - 5);
    display.print("Resetting...");
    Setup_EEPROM();
  }
}

void Back(){}
