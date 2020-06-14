#include "food.h"
#include "game_window.h"
#include "keys.h"
#include "snake.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GAME_WINDOW_LINES  40
#define GAME_WINDOW_COLS   80
#define GAME_WINDOW_Y      LINES / 2 - GAME_WINDOW_LINES / 2
#define GAME_WINDOW_X      COLS  / 2 - GAME_WINDOW_COLS  / 2

#define GAMEOVER_WINDOW_LINES  GAME_WINDOW_LINES / 2
#define GAMEOVER_WINDOW_COLS   GAME_WINDOW_COLS  / 2
#define GAMEOVER_WINDOW_Y      GAME_WINDOW_Y + GAMEOVER_WINDOW_LINES / 2
#define GAMEOVER_WINDOW_X      GAME_WINDOW_X + GAMEOVER_WINDOW_COLS  / 2

#define SNAKE_Y            GAME_WINDOW_LINES / 2
#define SNAKE_X            GAME_WINDOW_COLS / 2
#define SNAKE_CAPACITY     (GAME_WINDOW_LINES - 2) * (GAME_WINDOW_COLS - 2)

#define SNAKE_SKIN      'o'
#define FOOD_SKIN       '*'


void setup_ncurses(void);
void gameover_window_mainloop(void);


/*
 * TODO:
 */
int main(void)
{
    setup_ncurses();

    game_window_t game_window;
    snake_t snake;
    food_t food;

    game_window_init(&game_window, GAME_WINDOW_LINES, GAME_WINDOW_COLS, GAME_WINDOW_Y, GAME_WINDOW_X);
    snake_init(&snake, &game_window, SNAKE_CAPACITY, SNAKE_Y, SNAKE_X, SNAKE_SKIN);
    food_init(&food, &game_window, FOOD_SKIN);

    int key;
    int score = 0;

    while ((key = getch()) != QUIT) {

        if (!snake_move(&snake, &game_window, key))
            gameover_window_mainloop();

        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            ++score;
            snake_grow(&snake);
            food_set_random_coords(&food, &game_window);
        }

        food_draw(&food, &game_window);
        snake_draw(&snake, &game_window);

        /* mvwprintw(stdscr, 1, 1, "Score: %d", score); */
        /* mvwprintw(stdscr, 2, 1, "Length: %d", snake.length); */

        game_window_refresh(&game_window);
    }

    game_window_free(&game_window);
    snake_free(&snake);
    endwin();

    return EXIT_SUCCESS;
}


void gameover_window_mainloop()
{
    WINDOW* gameover_window = newwin(GAMEOVER_WINDOW_LINES, GAMEOVER_WINDOW_COLS,
                                     GAMEOVER_WINDOW_Y, GAMEOVER_WINDOW_X);

    int key;
    while ((key = getch()) != QUIT) {
        // print score and repeat again exit.
        mvwprintw(gameover_window, 1, 1, "game over");
        box(gameover_window, 0, 0);
        wrefresh(gameover_window);
    }
}


void setup_ncurses(void)
{
    initscr();
    noecho();
    curs_set(0);
    halfdelay(1);
    srand(time(NULL));
}
