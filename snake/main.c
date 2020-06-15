#include "error.h"
#include "food.h"
#include "game_window.h"
#include "snake.h"
#include "utils.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GAME_WINDOW_LINES 30
#define GAME_WINDOW_COLS 60
#define QUIT 'q'


void setup_ncurses(void);
void score_print(int score, game_window_t*);


int main(void)
{
    setup_ncurses();
    srand(time(NULL));

    game_window_t game_window;
    snake_t snake;
    food_t food;

    int status;
    if ((status = game_window_init(&game_window, GAME_WINDOW_LINES, GAME_WINDOW_COLS))) {
        endwin();
        print_error(status);
        return EXIT_FAILURE;
    }

    if ((status = snake_init(&snake, &game_window))) {
        endwin();
        print_error(status);
        return EXIT_FAILURE;
    }

    food_init(&food, &game_window);

    int key;
    int score = 0;

    while ((key = getch()) != QUIT && snake_move(&snake, &game_window, key)) {
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            snake_grow(&snake);
            food_set_random_coords(&food, &game_window);
            ++score;
        }

        food_draw(&food, &game_window);
        snake_draw(&snake, &game_window);
        score_print(score, &game_window);

        box(game_window.frame, 0, 0);
        wrefresh(game_window.frame);
    }

    game_window_free(&game_window);
    snake_free(&snake);
    endwin();

    puts("Game over. Thanks for playing.");
    return EXIT_SUCCESS;
}


void setup_ncurses(void)
{
    initscr();
    noecho();
    curs_set(0);
    start_color();
    halfdelay(1);
}


void score_print(int score, game_window_t* win)
{
    int y, _;
    getbegyx(win->frame, y, _);

    static char format[128];
    snprintf(format, sizeof(format), "Score: %d", score);
    mvprintw(y - 1, str_center(format, COLS), format);
}
