// ########################
// ####### MENU BAR #######
// ########################

#define N_OPTIONS 5               // Number of options on the menu
#define BACKGROUND 219            // Background colour of unselected item
#define SELECTED_BACKGROUND 182   // Background colour of selected item

void Menu_Loop(){
  unsigned char is_done = false;

  // Initialise cursor
  unsigned char y = 0;
  display.fontColor(TS_8b_Black, BACKGROUND);

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
    if (is_clicked(TSButtonUpperRight)){
      ExecuteOption(y);
      is_done = true;
    }
  }
  
  // Change font back
  display.fontColor(TS_8b_White, TS_8b_Black);
}

void Draw_Menu(unsigned char y){

  // If need be, can be more memory efficient at the expense of cancer
  char MenuOptions[N_OPTIONS][16] = {"To Do List", "Preferences", "Achievements", "Reset", "Back"};

  // Set parameters
  unsigned char rec_h = 10;
  unsigned char rec_w = 66;
  unsigned char left_pad = 3;
  unsigned char menu_left_pad = 5;
  unsigned char menu_top_pad = 5;
  
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

void ToDoList_Loop(){}
void Preference_Loop(){}
void Achievements_Loop(){}
void Reset_Loop(){}
void Back(){}
