#define MENU_COL 242
#define MENU_SHADOW 183
#define HEADER_COL 219

void Stats_Screen_Loop(){
  bool is_done = false;

  display.drawRect(9+2, 5+2, 73, 86, TSRectangleFilled, MENU_SHADOW);
  display.drawRect(9, 5, 73, 86, TSRectangleFilled, MENU_COL);
  display.drawRect(9, 5, 73, 12, TSRectangleFilled, HEADER_COL);

  // Print header
  char header[6][20] = {"Statistics", "Level: ", "Exp: ", "Trees: ", "Completed: ", "Failed: "};
  char text[6];

  itoa(GetGameVariables(1), text, 10);
  strcat(header[1], text);
  itoa(GetGameVariables(0), text, 10);
  strcat(header[2], text);
  itoa(GetGameVariables(0) / 15, text, 10);
  strcat(header[3], text);
  itoa(GetGameVariables(2), text, 10);
  strcat(header[4], text);
  itoa(GetGameVariables(3), text, 10);
  strcat(header[5], text);
  
  for (unsigned char i = 0; i < 6; ++i){
    display.setCursor(Rx/2 - display.getPrintWidth(header[i])/2 - 4, 7 + 9*i);
    if (i == 0) print_line(header[i], HEADER_COL, 0);
    else print_line(header[i], MENU_COL, 0);
  }

  while (!is_done){
    if (is_any_button()){
      while(is_any_button()){}
      is_done = true;
    }
  }
}
