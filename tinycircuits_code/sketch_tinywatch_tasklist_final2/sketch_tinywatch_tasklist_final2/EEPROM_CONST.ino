// ###########################################
// ####### ALL EEPROM OPERATIONS #############
// ###########################################

#include <EEPROM.h>
#include <string.h>
#include "const.h"

// ###########################################
// ####### VARIABLES TO STORE IN EEPROM ######
// ###########################################

unsigned char IS_FIRST; // If 0: store default values. Else continue with values in EEPROM

typedef struct {

  unsigned char BRIGHTNESS;
  unsigned char some_other_value;
  
}PREFERENCES;

typedef struct {

  unsigned char EXP;
  unsigned char LEVEL;
  
}GAME_VARIABLES;


// ###########################################
// ######## POINTERS IN EEPROM ###############
// ###########################################

const int IS_FIRST_PTR = 0;
const int PREFERENCES_PTR = IS_FIRST_PTR + 2; // +2 instead of +1 because memory is wordsized. I can fit another flag before this because 1 byte is unused.
const int TODO_LIST_PTR = PREFERENCES_PTR + sizeof(PREFERENCES);
const int GAME_VARIABLES_PTR = TODO_LIST_PTR + (LEN_TODO + 1) * N_TODO;

// ##########################################
// ######## SETTING UP EEPROM ###############
// ##########################################

// Setup on the first setup

void clear_EEPROM(){
  // Sets all values in EEPROM to 0
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void FirstSetup(){
  Serial.println("default");
  clear_EEPROM();
  
  // DEFAULT VALUES
  PREFERENCES pref;
  GAME_VARIABLES game;

  pref.BRIGHTNESS = 15;
  pref.some_other_value = 15;
  game.EXP = 0;
  game.LEVEL = 1;

  // Set default values
  WritePreferences(pref.BRIGHTNESS, 0);
  WritePreferences(pref.some_other_value, 1);
  WriteTodo("Sample TODO #1", 0);
  WriteTodo("Sample TODO #2", 1);
  WriteGameVariables(game.EXP, 0);
  WriteGameVariables(game.LEVEL, 1);
  
  WriteIsFirst(1);
}

// Setup
void Setup_EEPROM(){
  if (GetIsFirst() == 0) FirstSetup();
}

// ##########################################
// ######## GET VARIABLES IN EEPROM #########
// ##########################################

unsigned char GetIsFirst(){
  return EEPROM.read(IS_FIRST_PTR);
}

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

void WriteIsFirst(unsigned char* input){
  EEPROM.put(IS_FIRST_PTR, input);
}

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
