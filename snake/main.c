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
#define FOOD_POINTS     10

void setup_ncurses(void);
void score_draw(int score, WINDOW*);

/*
 * TODO:
 */
int main(void)
{
    setup_ncurses();
    srand(time(NULL));

    GameWindow game_win;
    Snake snake;
    Food food;

    game_window_init(&game_win, GAME_WIN_LINES, GAME_WIN_COLS, GAME_WIN_Y, GAME_WIN_X);
    snake_init(&snake, SNAKE_MAX_BODY, SNAKE_Y, SNAKE_X, NORTH);
    food_init(&food, &game_win);

    int key;
    int score = 0;
    bool game_won = false;

    while ((key = getch()) != _KEY_QUIT || game_won) {
        snake_update_dir(&snake, key);
        snake_update_yx(&snake, &game_win);

        if (snake.x == food.x && snake.y == food.y) {
            if (!snake_grow_body(&snake))
                game_won = true;
            else {
                score += FOOD_POINTS;
                food_set_random_yx(&food, &game_win);
            }
        }

        food_draw(&food, &game_win);
        snake_draw(&snake, &game_win);

        mvwprintw(stdscr, 1, 1, "Score: %d", score);
        mvwprintw(stdscr, 2, 1, "Length: %d", snake.length);

        game_window_refresh(&game_win);
    }

    // Game won screen here.

    game_window_free(&game_win);
    snake_free(&snake);
    endwin();

    return 0;
}


void setup_ncurses(void)
{
    initscr();
    noecho();
    curs_set(0);
    halfdelay(1);
}
