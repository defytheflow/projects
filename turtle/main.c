#include "menu.h"
#include "turtle.h"
#include "enemy.h"
#include "sprite.h"
#include "colors.h"

#include <ncurses.h>

#include <stdlib.h>
#include <string.h>


void draw_bg(void)
{
    attron(COLOR_PAIR(BG_COLOR));
    for (int y = 0; y < LINES; ++y) {
        mvhline(y, 0, ' ', COLS);
    }
    attroff(COLOR_PAIR(BG_COLOR));
}

int main(void)
{
        /* Don't touch us! */
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);
        start_color();
        /* End */

        init_pair(BG_COLOR, COLOR_BLACK, COLOR_CYAN);
        init_pair(TURTLE_COLOR, COLOR_BLACK, COLOR_CYAN);
        init_pair(PLATYPUS_COLOR, COLOR_BLACK, COLOR_CYAN);
        init_pair(STINGRAY_COLOR, COLOR_BLACK, COLOR_CYAN);

        Turtle t;
        turtle_init(&t, "skins/turtle.txt", TURTLE_COLOR);

        Enemy st;
        enemy_init(&st, "skins/stingray.txt", STINGRAY_COLOR);

        Enemy pl;
        enemy_init(&pl, "skins/platypus.txt", PLATYPUS_COLOR);


        menu_init(); // init menu_win
        MenuChoice choice = menu_mainloop();
        clear();

        switch (choice) {
        case MENU_PLAY: {
                halfdelay(1);
                draw_bg();
                for (;;) {
                        int ch = getch();

                        turtle_update(&t, ch);
                        enemy_update(&pl);
                        enemy_update(&st);

                        sprite_draw(&pl.sprite);
                        sprite_draw(&st.sprite);
                        sprite_draw(&t.sprite);

                        box(stdscr, 0, 0);
                        refresh();
                }
        }
                break;
        case MENU_SETTINGS:
                break;
        case MENU_EXIT:
                break;
        }
        
        turtle_del(&t);
        // enemy_del(&pl);
        // enemy_del(&st);

        endwin();
        return EXIT_SUCCESS;
}
