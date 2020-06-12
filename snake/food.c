#include "food.h"
#include "game_window.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>


void food_init(Food* food, GameWindow* game_win)
{
    food->body = '*';
    food_set_random_yx(food, game_win);
}


void food_set_random_yx(Food* food, GameWindow* game_win)
{
    do {
        food->y = rand() % game_win->lines;
        food->x = rand() % game_win->cols;
    } while (yx_occupied(game_win, food->y, food->x) ||
             yx_collides_with_border(game_win, food->y, food->x));
    game_win->cells[food->y][food->x] = food->body;
}


void food_draw(Food* food, GameWindow* game_win)
{
    mvwaddch(game_win->frame, food->y, food->x, food->body);
}

