// #######################################
// ####### DEALS WITH BUTTONS ############
// #######################################

bool is_clicked(unsigned char button){
  if (display.getButtons(button)){
    button_loop(button);
    return true;
  }
  return false;
}

void button_loop(unsigned char button){
  bool is_done = false;
  while (!is_done){
    if (!display.getButtons(button)) is_done = true;
  }
}
