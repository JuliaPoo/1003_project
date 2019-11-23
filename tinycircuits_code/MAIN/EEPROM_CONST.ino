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
  unsigned char TIMEOUT; // Given in multiples of 15s
  unsigned char POWER_SAVING_LEVEL;
  unsigned char temp; // Cuz memory size has to be even
  
}PREFERENCES;

typedef struct {

  unsigned char EXP;
  unsigned char LEVEL;
  unsigned char TasksCompleted;
  unsigned char TasksFailed;
  
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
  clear_EEPROM();
  
  // DEFAULT VALUES
  PREFERENCES pref;
  //GAME_VARIABLES game;

  pref.BRIGHTNESS = 15;
  pref.TIMEOUT = 2;
  pref.POWER_SAVING_LEVEL = 0;
  
  //game.EXP = 0;
  //game.LEVEL = 0;
  //game.TasksCompleted = 0;
  //game.TasksFailed = 0;
  
  // Set default values
  WritePreferences(pref.BRIGHTNESS, 0);
  WritePreferences(pref.TIMEOUT, 1);
  WritePreferences(pref.POWER_SAVING_LEVEL, 2);
  
  //WriteTodo("Sample TODO #1", 0);
  //WriteTodo("Sample TODO #2", 1);
  //char temp[LEN_TODO] = "Testing a Really Long String";
  //WriteTodo(temp, 2);
  
  //WriteGameVariables(game.EXP, 0);
  //WriteGameVariables(game.LEVEL, 1);
  //WriteGameVariables(game.TasksCompleted, 2);
  //WriteGameVariables(game.TasksFailed, 3);
  
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
  // pos=1: gets TIMEOUT
  // pos=2: gets POWER_SAVING_LEVEL
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
  // pos=0: Gets EXP
  // pos=1: Gets LEVEL
  // pos=2: Gets TasksCompleted
  // pos=3: Gets TasksFailed
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
  // pos=2: writes TasksCompleted
  // pos=3: writes TasksFailed
  EEPROM.put(GAME_VARIABLES_PTR + pos, input);
}
