void Idle_Loop(long* UseTime){
  
  bool is_done = false;
  display.fontColor(TS_8b_White, TS_8b_Black);

  int miniclock = 0;
  unsigned char count = 0;
  while (!is_done){
    Draw_Idle_Screen(&miniclock, &count);
    if (is_any_button()){
      is_done = true;
      *UseTime = millis();
    }
  }
}

void Draw_Idle_Screen(int* miniclock, unsigned char* count){
  
  *miniclock = (*miniclock + 1) % 10000;
  if (*miniclock % 500 != 0) return;

  int i;
  char UwU[11] = "(-.-)]";
  for (i = 0; i<*count; ++i){
    strcat(UwU, "z");
  }
  unsigned char width = display.getPrintWidth(UwU);
  display.setCursor(48-(width/2),Ry/2 - 5);

  display.clearScreen();
  display.print(UwU);

  *count = (*count + 1) % 5;
  
}
