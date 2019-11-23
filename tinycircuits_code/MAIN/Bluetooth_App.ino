

uint8_t ble_rx_buffer[21];
uint8_t ble_rx_buffer_len = 0;
uint8_t ble_connection_state = false;
#define PIPE_UART_OVER_BTLE_UART_TX_TX 0

bool RecieveData(char* output){

  // Waits for an input until a button is clicked
  // If input arrive, return true
  // else returns false

  bool is_done = false;
  
  while(!is_done){
    
    aci_loop();

    if (is_any_button()){
      while (is_any_button()){}
      return false;
    }
    
    if (ble_rx_buffer_len){
      is_done = true;
    }
  }

  ble_rx_buffer_len = 0;
  strcpy(output, (char*)ble_rx_buffer);
  return true;
}

bool SendData(char* data){

  // Sends data, data has to be less than 19 chars long
  
  aci_loop();
  delay(100);
  if (!lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, (uint8_t*)data, strlen(data) + 1)){
    return false;
  }
  return true;
}


bool GetTaskFromBluetooth(){
  
  BLEsetup();

  char text[20];
  while (!ble_connection_state){aci_loop();} // Wait to be connected to

  delay(2000);
  
  //strcpy(text, "\n\nHello! I'm Kaho!\n");
  //SendData(text);
  
  strcpy(text, "\n\nInput:\n");
  SendData(text);

  if (RecieveData(text)){
    add_task_to_tasklist(text);
    
    //strcpy(text, "\n\nReceived!\n");
    //SendData(text);
    //strcpy(text, "\n\nHope you can\n");
    //SendData(text);
    //strcpy(text, "\n\ncomplete it!\n");
    //SendData(text);

    ble_connection_state = false;
    return true;
  }
  ble_connection_state = false;
  return false;
  
}
