#include "food.h"
#include "color.h"
#include "game_window.h"
#include "utils.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#define FOOD_SKIN '*'


void food_init(food_t* food, game_window_t* win)
{
    init_pair(FOOD_COLOR, COLOR_RED, COLOR_BLACK);
    food_set_random_coords(food, win);
}


void food_draw(const food_t* food, const game_window_t* win)
{
    wattron(win->frame, COLOR_PAIR(FOOD_COLOR));
    mvwaddch(win->frame, food->y, food->x, FOOD_SKIN);
    wattroff(win->frame, COLOR_PAIR(FOOD_COLOR));
}


void food_set_random_coords(food_t* food, game_window_t* win)
{
    do {
        food->y = random_range(1, win->lines - 2);
        food->x = random_range(1, win->cols - 2);
    } while (!game_window_cell_empty(win, food->y, food->x));
    game_window_occupy_cell(win, food->y, food->x);
}
