#include "food.h"
#include "game_window.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>


void food_init(food_t* food, game_window_t* game_win, char skin)
{
    food->skin = skin;
    food_set_random_yx(food, game_win);
}


void food_draw(food_t* food, game_window_t* game_win)
{
    mvwaddch(game_win->frame, food->y, food->x, food->skin);
}


void food_set_random_yx(food_t* food, game_window_t* game_win)
{
    do {
        food->y = rand() % game_win->lines;
        food->x = rand() % game_win->cols;
    } while (yx_occupied(game_win, food->y, food->x) ||
             yx_collides_with_border(game_win, food->y, food->x));
    game_win->cells[food->y][food->x] = food->skin;
}
