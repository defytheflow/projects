#include "snake.h"
#include "game_window.h"
#include "keys.h"

#include <ncurses.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SNAKE_BODY        'o'
#define SNAKE_EMPTY_BODY  '\0'


void snake_init(Snake* snake, int capacity, int y, int x, Direction dir)
{
    snake->y = y;
    snake->x = x;
    snake->dir = dir;
    snake->body = (char*) malloc(capacity);
    assert(snake->body != NULL);
    memset(snake->body, SNAKE_EMPTY_BODY, capacity);
    snake->body[0] = SNAKE_BODY;
    snake->capacity = capacity;
    snake->length = 1;
}


void snake_free(Snake* snake)
{
    free(snake->body);
}


void snake_draw(Snake* snake, GameWindow* game_win)
{
    mvwaddch(game_win->frame, snake->y, snake->x, snake->body[0]);
}


bool snake_grow_body(Snake* snake)
{
    if (snake->length == snake->capacity)
        return false;

    snake->body[snake->length++] = SNAKE_BODY;
    return true;
}


void snake_update_dir(Snake* snake, int key)
{
    switch (key) {
    case _KEY_UP:
        snake->dir = NORTH;
        break;
    case _KEY_LEFT:
        snake->dir = WEST;
        break;
    case _KEY_DOWN:
        snake->dir = SOUTH;
        break;
    case _KEY_RIGHT:
        snake->dir = EAST;
        break;
    }
}


void snake_update_yx(Snake* snake, GameWindow* game_win)
{
    switch (snake->dir) {
    case NORTH:
        --snake->y;
        break;
    case WEST:
        --snake->x;
        break;
    case SOUTH:
        ++snake->y;
        break;
    case EAST:
        ++snake->x;
        break;
    }

    /* Border teleport */
    if (snake->x == 0)
        snake->x = game_win->cols - 1;
    else if (snake->x == game_win->cols - 1)
        snake->x = 1;

    if (snake->y == 0)
        snake->y = game_win->lines - 1;
    else if (snake->y == game_win->lines - 1)
        snake->y = 1;
}
