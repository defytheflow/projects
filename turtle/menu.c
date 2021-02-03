#include "menu.h"

#include <ncurses.h>

#include <stdbool.h>
#include <string.h>

WINDOW* menu_win = NULL;

static int center_text(int width, const char* s);

void menu_init()
{
        menu_win = newwin(MENU_HEIGHT, MENU_WIDTH, MENU_Y, MENU_X);
}

MenuChoice menu_mainloop()
{
        int choice = 0;
        int highlighted_choice = 0;

        const char* menu_choices[] = {
            "play",
            "settings",
            "exit",
        };

        // Draw MENU_TITLE
        mvprintw(MENU_Y-1, MENU_X+center_text(MENU_WIDTH, MENU_TITLE), MENU_TITLE);
        refresh();

        bool menu_run = true;
        while (menu_run) {

                box(menu_win, 0, 0);
                for (int i = 0; i < MENU_LENGTH; ++i) {
                        if (i == highlighted_choice)
                                wattron(menu_win, A_REVERSE);
                        wmove(menu_win, i+1, center_text(MENU_WIDTH, menu_choices[i]));
                        wprintw(menu_win, menu_choices[i]);
                        wattroff(menu_win, A_REVERSE);
                }
                wrefresh(menu_win);

                choice = wgetch(menu_win);
                switch (choice) {
                case 'j':
                        ++highlighted_choice;
                        if (highlighted_choice >= MENU_LENGTH)
                                highlighted_choice = MENU_LENGTH - 1;
                        break;
                case 'k':
                        --highlighted_choice;
                        if (highlighted_choice < 0)
                                highlighted_choice = 0;
                        break;
                case '\n':
                        menu_run = false;
                }
        }

        return (MenuChoice) highlighted_choice;
}

static int center_text(int width, const char* s)
{
        return (width - strlen(s)) / 2;
}
