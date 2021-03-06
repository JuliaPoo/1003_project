// #######################################
// ####### DEALS WITH BUTTONS ############
// #######################################

bool is_clicked(unsigned char button){
  // Returns true only upon the release of the pressed button.
  // Prevents multiple click events being generated by a single click
  
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
