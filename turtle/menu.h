#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

#define MENU_LENGTH      3
#define MENU_WIDTH       20
#define MENU_HEIGHT      MENU_LENGTH + 2
#define MENU_X           COLS / 2  - MENU_WIDTH  / 2
#define MENU_Y           LINES / 2 - MENU_HEIGHT / 2
#define MENU_TITLE       "MENU"

typedef enum {
    MENU_PLAY,
    MENU_SETTINGS,
    MENU_EXIT,
} MenuChoice;

extern WINDOW* menu_win;

void menu_init();
MenuChoice menu_mainloop();

#endif
