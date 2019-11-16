#include <EEPROM.h>
#include <string.h>
#include "const.h"

// ###########################################
// ####### VARIABLES TO STORE IN EEPROM ######
// ###########################################

typedef struct {

  unsigned char BRIGHTNESS;
  unsigned char some_other_value;
  
}PREFERENCES;

char TODO_LIST[N_TODO][LEN_TODO + 1];

typedef struct {

  unsigned char EXP;
  unsigned char LEVEL;
  
} GAME_VARIABLES;


// ###########################################
// ######## POINTERS IN EEPROM ###############
// ###########################################

const int PREFERENCES_PTR = 0;
const int TODO_LIST_PTR = PREFERENCES_PTR + sizeof(PREFERENCES);
const int GAME_VARIABLES_PTR = TODO_LIST_PTR + (LEN_TODO + 1) * N_TODO;

// ##########################################
// ######## SETTING UP EEPROM ###############
// ##########################################

// Setup on the first setup
bool is_first = true;

void clear_EEPROM(){
  // Sets all values in EEPROM to 0
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void FirstSetup(){
  clear_EEPROM();
  
  // DEFAULT VALUES
  PREFERENCES pref;
  GAME_VARIABLES game;

  pref.BRIGHTNESS = 10;
  pref.some_other_value = 15;
  strcpy(TODO_LIST[0], "Sample TODO #1");
  strcpy(TODO_LIST[1], "Sample TODO #2");
  game.EXP = 0;
  game.LEVEL = 1;

  // Set default values
  WritePreferences(pref.BRIGHTNESS, 0);
  WritePreferences(pref.some_other_value, 1);
  WriteTodo(TODO_LIST[0], 0);
  WriteTodo(TODO_LIST[1], 1);
  WriteGameVariables(game.EXP, 0);
  WriteGameVariables(game.LEVEL, 1);
  
  is_first = false;
}

// Setup
void Setup_EEPROM(){
  if (is_first) FirstSetup();
}

// ##########################################
// ######## GET VARIABLES IN EEPROM #########
// ##########################################

unsigned char GetPreferences(unsigned char pos){
  // pos=0: gets brightness
  // pos=1: gets some_other_value
  // Returns the value in preference

  return EEPROM.read(pos + PREFERENCES_PTR);
}

void GetTodo(char* output, unsigned char index){
  // Gets the todo string at index of todo
  // copies the string to output

  int start = TODO_LIST_PTR + index*(LEN_TODO+1);
  unsigned char i;
  for (i = 0; i < LEN_TODO + 1; ++i){
    output[i] = EEPROM.read(start + i);
  }
}

unsigned char GetGameVariables(unsigned char pos){
  // pos=1: Gets EXP
  // pos=2: Gets LEVEL
  // Returns the value in game variables

  return EEPROM.read(pos + GAME_VARIABLES_PTR);
}

// ##########################################
// ######## WRITE VARIABLES TO EEPROM #######
// ##########################################

void WriteTodo(char* input, unsigned char index){
  // Writes todo string into EEPROM
  // input is the string to write
  // index is index in the todo
  
  int start = TODO_LIST_PTR + index*(LEN_TODO + 1);
  unsigned char i;
  for (i = 0; i < LEN_TODO + 1; ++i){
    EEPROM.put(start + i, input[i]);
  }
}

void WritePreferences(unsigned char input, unsigned char pos){
  // Writes preferences into EEPROM
  // pos=0: writes brightness
  // pos=1: writes some_other_value
  EEPROM.put(PREFERENCES_PTR + pos, input);
}

void WriteGameVariables(unsigned char input, unsigned char pos){
  // Writes game variables into EEPROM
  // pos=0: writes EXP
  // pos=1: writes LEVEL
  EEPROM.put(GAME_VARIABLES_PTR + pos, input);
}
