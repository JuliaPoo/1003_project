#include <TinyScreen.h>
#include <Wire.h>
#include <SPI.h>
#include "const.h"

// added functions
#include <Time.h>
#include <stdlib.h>
#include <string.h>

#define TASKS_STORAGE_MAX N_TODO
#define LINES_LENGTH LEN_TODO+1
#define ELEMENTS_PER_PAGE 4 // Starting from 0: 0,1,2,3,4 (5 elements total)
#define DISPLAY_BOX_CHAR_LIMIT 13

#define MENU_BACKGROUND_COL 183
#define MENU_ARROW_COL 182
#define NORMAL_TEXT_BG 219
#define SELECTED_TEXT_BG 182
#define POPUP_BACKGROUND_COL 242

TinyScreen display = TinyScreen(TinyScreenDefault);

void slice_str(char * buff, const char * str, size_t start, size_t end){
  size_t j = 0;
  for ( size_t i = start; i <= end; ++i ) {
      buff[j++] = str[i];
  }
  buff[j] = 0;
}

void drawCircle(int x0, int y0, int radius, uint8_t color){
  int x = radius; int y = 0; int radiusError = 1-x;
  while(x >= y){
    display.drawPixel(x + x0, y + y0, color);
    display.drawPixel(y + x0, x + y0, color);
    display.drawPixel(-x + x0, y + y0, color);
    display.drawPixel(-y + x0, x + y0, color);
    display.drawPixel(-x + x0, -y + y0, color);
    display.drawPixel(-y + x0, -x + y0, color);
    display.drawPixel(x + x0, -y + y0, color);
    display.drawPixel(y + x0, -x + y0, color);
    y++;
    if (radiusError<0){radiusError += 2 * y + 1;}
    else{x--;radiusError += 2 * (y - x) + 1;}}
}

void print_line(char* s, unsigned char text_col, unsigned char background_col){
   display.fontColor(background_col, text_col);
   display.print(s);
}

void arrow_up_normal(unsigned char col){
  display.drawRect(4, 2, 1, 2, TSRectangleFilled, col);
  display.drawRect(3, 4, 3, 2, TSRectangleFilled, col);
  display.drawRect(2, 6, 5, 2, TSRectangleFilled, col);
  display.drawRect(1, 8, 7, 2, TSRectangleFilled, col);
  }
void arrow_down_normal(unsigned char col){
  display.drawRect(1, 53, 7, 2, TSRectangleFilled, col);
  display.drawRect(2, 55, 5, 2, TSRectangleFilled, col);
  display.drawRect(3, 57, 3, 2, TSRectangleFilled, col);
  display.drawRect(4, 59, 1, 2, TSRectangleFilled, col);
}
void out_box(){
  display.drawRect(84, 0, 11, 11, TSRectangleFilled, 158, 134, 200);
  //the x on the out
  // x, y, color
  display.drawPixel(85, 1, TS_8b_White);display.drawPixel(93, 1, TS_8b_White);
  display.drawPixel(86, 2, TS_8b_White);display.drawPixel(92, 2, TS_8b_White);
  display.drawPixel(87, 3, TS_8b_White);display.drawPixel(91, 3, TS_8b_White);
  display.drawPixel(88, 4, TS_8b_White);display.drawPixel(90, 4, TS_8b_White);
  display.drawPixel(89, 5, TS_8b_White);
  display.drawPixel(88, 6, TS_8b_White);display.drawPixel(90, 6, TS_8b_White);
  display.drawPixel(87, 7, TS_8b_White);display.drawPixel(91, 7, TS_8b_White);
  display.drawPixel(86, 8, TS_8b_White);display.drawPixel(92, 8, TS_8b_White);
  display.drawPixel(85, 9, TS_8b_White);display.drawPixel(93, 9, TS_8b_White);
}
void sel_box(){
  //select
  display.drawRect(84, 52, 11, 12, TSRectangleFilled, 229, 181, 103);
  
  // circle
  drawCircle(89, 57, 4, TS_8b_White); 
}
    
void init_UI(){
  display.setFont(thinPixel7_10ptFontInfo);
  display.clearScreen(); 
  display.setCursor(9,0);
  
  // background
  display.drawRect(0, 0, 95, 64, TSRectangleFilled, MENU_BACKGROUND_COL);
  
  // header
  print_line("To-do list", MENU_BACKGROUND_COL, 0);

  // arrow up and down
  arrow_up_normal(MENU_ARROW_COL);
  arrow_down_normal(MENU_ARROW_COL);
  out_box();
  sel_box();
}

void add_task_to_tasklist(char *input_string){
  short int i;
  char temp[LINES_LENGTH];
  for (i = 0; i < TASKS_STORAGE_MAX; i++){
    GetTodo(temp, i);
    if (temp[0] == '\0'){
      if(strlen(input_string) < LINES_LENGTH){
        WriteTodo(input_string, i);
        break;
      } else {
        input_string[LINES_LENGTH] = '\0';
        WriteTodo(input_string, i);
        break;
      }
    }
  }
}

void truncate_text(char* output, char* text, short int start_pos, short int width, bool* is_truncated){
  char temp[LINES_LENGTH + 1];
  char text_cut[LINES_LENGTH + 1];
  unsigned char len = strlen(text);

  if (len == 0){strcpy(output, ""); return;}
  slice_str(text_cut, text, start_pos, len-1);

  if (display.getPrintWidth(text_cut) < width - 4){
    strcpy(output, text_cut);
    *is_truncated = false;
    return;
  }
  
  unsigned char i = 1;
  strcpy(temp, text_cut);
  temp[i] = 0;
  while (display.getPrintWidth(temp) < width - display.getPrintWidth("...") - 4){
    ++i;
    strcpy(temp, text_cut);
    temp[i] = 0;
  }
  temp[strlen(temp)-2] = 0;
  strcat(temp, "...");
  strcpy(output, temp);
  *is_truncated = true;
  return;
}

void show_text(short int selector, short int pos_in_page){
  unsigned char first = max(0, selector - pos_in_page);
  unsigned char last = min(TASKS_STORAGE_MAX - 1, selector + (ELEMENTS_PER_PAGE - pos_in_page) + 1);

  bool is_truncated;
  char text[LINES_LENGTH];
  char temp[LINES_LENGTH];
  short int i, row = 0;
  for (i = first; i < last; ++i){

    GetTodo(temp, i);
    truncate_text(text, temp, 0, 84, &is_truncated);
    
    display.setCursor(3, 11 + 10 * row);
    if (selector == i) print_line(text, SELECTED_TEXT_BG, 0);
    else print_line(text, NORMAL_TEXT_BG, 0);
    ++row;
  }
}

void display_menu(short int selector, short int pos_in_page){
  // colour whole inner menu
  display.drawRect(0, 11, 84, 58, TSRectangleFilled, NORMAL_TEXT_BG);
  
  // highlight
  display.drawRect(0, 11 + 10 * pos_in_page, 84, 10, TSRectangleFilled, SELECTED_TEXT_BG);

  show_text(selector, pos_in_page);
}

void popup_buttons(int yes){
  if (yes == 1){
    display.setCursor(19, 25);
    print_line(" Yes! ", SELECTED_TEXT_BG, 0);
    display.setCursor(19, 37);
    print_line(" Not yet. ", NORMAL_TEXT_BG, 0);
  } 
  if (yes == 0){
    display.setCursor(19, 25);
    print_line(" Yes! ", NORMAL_TEXT_BG, 0);
    display.setCursor(19, 37);
    print_line(" Not yet. ", SELECTED_TEXT_BG, 0);
  }
}

void open_popupbox(int select_index){
  char popup_loop_end = '0';
  char temp[LINES_LENGTH];
  // colour whole inner menu partially
  display.drawRect(13, 12, 65, 41, 0, 0); // Outline
  display.drawRect(14, 13, 63, 39, TSRectangleFilled, POPUP_BACKGROUND_COL);
  display.setCursor(14, 13);
  print_line("Finish task?", POPUP_BACKGROUND_COL, 0);
  
  short int complete_task = 0;
  popup_buttons(complete_task);
  
  while (popup_loop_end == '0'){
      if (is_clicked(TSButtonUpperLeft)){
        if (complete_task == 1){
          complete_task = 0;
        } else if (complete_task == 0){
          complete_task = 1;
        }
        popup_buttons(complete_task);
      }
      if (is_clicked(TSButtonLowerLeft)){
        if (complete_task == 1){
          complete_task = 0;
        } else if (complete_task == 0){
          complete_task = 1;
        }
        popup_buttons(complete_task);
      }
      if (is_clicked(TSButtonUpperRight)){
        break;  
      }
      if (is_clicked(TSButtonLowerRight)){
        if (complete_task == 0){
          break;
        }
        if (complete_task == 1){
        // delete the entry, mark as complete and rearrange.
          WriteTodo("\0", select_index);
          int counter;
          for (counter = 0; counter < TASKS_STORAGE_MAX; counter++){
            if (counter > select_index){
              GetTodo(temp, counter);
              WriteTodo(temp, counter-1);
            }
          }
          break;
        }
      }
  }
}

void TEMP_TASKLIST(){
  // Hardcoded tasks
  add_task_to_tasklist("Hello world!");
  add_task_to_tasklist("Hello world");
  add_task_to_tasklist("A very long string string!!!!!");
  add_task_to_tasklist("Lorem Ipsum");
  add_task_to_tasklist("Dolor Sit Amet");
  add_task_to_tasklist("Let them");
  add_task_to_tasklist("Eat cake");
  add_task_to_tasklist("just a test of");
  add_task_to_tasklist("1234567890-=");
}

void UI(){
  bool is_done = false;
  short int pos_in_page = 0;
  short int selector = 0;
  init_UI();  

  TEMP_TASKLIST();
      
  display_menu(selector, pos_in_page);

  while (!is_done){
    animate_text_loop(selector, pos_in_page);
    button_controller_loop(&selector, &pos_in_page);
  }
}

void animate_text_loop(short int selector, short int pos_in_page){
  bool is_done = false;
  bool is_truncated = true;
  char text[LINES_LENGTH];
  char temp[LINES_LENGTH];

  short int truncate = 0;

  while (!is_done){
    if (millis()/10 % 10 == 0){

      GetTodo(temp, selector);
      truncate_text(text, temp, truncate, 84, &is_truncated);

      display.setCursor(3, 11 + 10 * pos_in_page);
      print_line(text, SELECTED_TEXT_BG, 0);
      
      ++ truncate;
      
    }
    if (display.getButtons(TSButtonUpperLeft) || 
        display.getButtons(TSButtonUpperRight)|| 
        display.getButtons(TSButtonLowerLeft) || 
        display.getButtons(TSButtonUpperRight)){
          
      is_done = true;
    }

    if (!is_truncated){
      is_done = true;
    }
  }
}

void button_controller_loop(short int *selector, short int *pos_in_page){
  bool is_done = false;

  while (!is_done){
    if (is_clicked(TSButtonUpperLeft)){
      
      if (*selector == 0){
        *pos_in_page = ELEMENTS_PER_PAGE;
      } else *pos_in_page = max(1, *pos_in_page) - 1;
      *selector = (TASKS_STORAGE_MAX + *selector - 1) % TASKS_STORAGE_MAX;
      
      display_menu(*selector, *pos_in_page);

      is_done = true;
    }

    
    if (is_clicked(TSButtonLowerLeft)){
      if (*selector == TASKS_STORAGE_MAX-1){
        *pos_in_page = 0;
      } else *pos_in_page = min(ELEMENTS_PER_PAGE, *pos_in_page + 1);
      *selector = (*selector + 1) % TASKS_STORAGE_MAX;

      display_menu(*selector, *pos_in_page);

      is_done = true;
    }

    if (is_clicked(TSButtonLowerRight)){
      open_popupbox(*selector);
      display_menu(*selector, *pos_in_page);
      is_done = true;
    }
    
  }
}


void setup(void) {
  // put your setup code here, to run once:
  Wire.begin();
  display.begin();
  display.setBrightness(15);  // 0 to 15 only
  Serial.begin(9600);
  FirstSetup();
  
}


void loop() {
  UI(); // draws the UI of the menu. launches a loop. when inside the loop and x is pressed, loop break.
}
