#include "food.h"
#include "game_window.h"
#include "keys.h"
#include "snake.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GAME_WIN_LINES  40
#define GAME_WIN_COLS   80
#define GAME_WIN_Y      LINES / 2 - GAME_WIN_LINES / 2
#define GAME_WIN_X      COLS / 2 - GAME_WIN_COLS / 2
#define SNAKE_Y         GAME_WIN_LINES / 2
#define SNAKE_X         GAME_WIN_COLS / 2
#define SNAKE_MAX_BODY  (GAME_WIN_LINES - 2) * (GAME_WIN_COLS - 2)
#define SNAKE_SKIN      'o'
#define FOOD_SKIN       '*'


void setup_ncurses(void);
void score_draw(int score, WINDOW*);

/*
 * TODO:
 */
int main(void)
{
    setup_ncurses();
    srand(time(NULL));

    game_window_t game_win;
    snake_t snake;
    food_t food;

    game_window_init(&game_win, GAME_WIN_LINES, GAME_WIN_COLS, GAME_WIN_Y, GAME_WIN_X);
    snake_init(&snake, &game_win, SNAKE_MAX_BODY, SNAKE_Y, SNAKE_X, SNAKE_SKIN);
    food_init(&food, &game_win, FOOD_SKIN);

    int key;
    int score = 0;
    bool game_won = false;

    while ((key = getch()) != _KEY_QUIT && !game_won) {
        snake_move(&snake, &game_win, key);

        if (snake_head(&snake).x == food.x && snake_head(&snake).y == food.y) {
            if (!snake_grow(&snake))
                game_won = true;
            else {
                ++score;
                food_set_random_yx(&food, &game_win);
            }
        }

        food_draw(&food, &game_win);
        snake_draw(&snake, &game_win);

        /* mvwprintw(stdscr, 1, 1, "Score: %d", score); */
        /* mvwprintw(stdscr, 2, 1, "Length: %d", snake.length); */

        game_window_refresh(&game_win);
    }

    // Game won screen here.

    game_window_free(&game_win);
    snake_free(&snake);
    endwin();

    return EXIT_SUCCESS;
}


void setup_ncurses(void)
{
    initscr();
    noecho();
    curs_set(0);
    halfdelay(1);
}
