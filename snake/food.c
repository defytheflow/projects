#include "food.h"
#include "game_window.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>


static int random_range(int low, int high);


void food_init(food_t* food, game_window_t* win, char skin)
{
    food->skin = skin;
    food_set_random_coords(food, win);
}


void food_draw(const food_t* food, const game_window_t* win)
{
    mvwaddch(win->frame, food->y, food->x, food->skin);
}


void food_set_random_coords(food_t* food, game_window_t* win)
{
    do {
        food->y = random_range(1, win->lines - 2);
        food->x = random_range(1, win->cols - 2);
    } while (!game_window_cell_empty(win, food->y, food->x));
    game_window_set_cell(win, food->y, food->x);
}


static int random_range(int low, int high)
{
    return rand() % (high - low + 1) + low;
}
