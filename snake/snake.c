#include "snake.h"
#include "game_window.h"
#include "keys.h"

#include <ncurses.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


static inline snake_body_t snake_head(snake_t* snake);
static inline snake_body_t snake_tail(snake_t* snake);
static void snake_update_direction(snake_t*, int key);
static void snake_update_coords(snake_t*, game_window_t*);
static void snake_body_update_coords(snake_body_t* body, game_window_t* win);


void snake_init(snake_t* snake, game_window_t* win, int capacity, int y, int x, char skin)
{
    snake->capacity = capacity;
    snake->length = 1;
    snake->skin = skin;

    snake->body = (snake_body_t*) malloc(sizeof(snake_body_t) * capacity);
    assert(snake->body != NULL);

    snake->body[0].y = y;
    snake->body[0].x = x;
    snake->body[0].dir = (direction_t) rand() % 4;

    game_window_set_cell(win, y, x);
}


void snake_free(snake_t* snake)
{
    free(snake->body);
}


void snake_draw(snake_t* snake, game_window_t* win)
{
    for (int i = 0; i < snake->length; ++i)
        mvwaddch(win->frame, snake->body[i].y, snake->body[i].x, snake->skin);
}


bool snake_grow(snake_t* snake)
{
    if (snake->length == snake->capacity)
        return false;

    switch (snake_tail(snake).dir) {
    case NORTH:
        snake->body[snake->length].y = snake_tail(snake).y + 1;
        snake->body[snake->length].x = snake_tail(snake).x;
        break;
    case WEST:
        snake->body[snake->length].y = snake_tail(snake).y;
        snake->body[snake->length].x = snake_tail(snake).x + 1;
        break;
    case SOUTH:
        snake->body[snake->length].y = snake_tail(snake).y - 1;
        snake->body[snake->length].x = snake_tail(snake).x;
        break;
    case EAST:
        snake->body[snake->length].y = snake_tail(snake).y;
        snake->body[snake->length].x = snake_tail(snake).x - 1;
        break;
    }

    snake->body[snake->length].dir = snake_tail(snake).dir;
    ++snake->length;

    return true;
}

/*
 * Returns false if collides with any part of itself.
 */
bool snake_move(snake_t* snake, game_window_t* win, int key)
{
    snake_update_direction(snake, key);
    snake_update_coords(snake, win);

    for (int i = 1; i < snake->length; ++i)
        if (snake_head(snake).y == snake->body[i].y && snake_head(snake).x == snake->body[i].x)
            return false;
    return true;
}


static void snake_update_direction(snake_t* snake, int key)
{
    for (int i = snake->length - 1; i > 0; --i)
        snake->body[i].dir = snake->body[i-1].dir;

    switch (key) {
    case MOVE_NORTH:
        snake->body[0].dir = (snake_head(snake).dir != SOUTH) ? NORTH : SOUTH;
        break;
    case MOVE_WEST:
        snake->body[0].dir = (snake_head(snake).dir != EAST) ? WEST : EAST;
        break;
    case MOVE_SOUTH:
        snake->body[0].dir = (snake_head(snake).dir != NORTH) ? SOUTH : NORTH;
        break;
    case MOVE_EAST:
        snake->body[0].dir = (snake_head(snake).dir != WEST) ? EAST : WEST;
        break;
    }
}


static void snake_update_coords(snake_t* snake, game_window_t* win)
{
    for (int i = 0; i < snake->length; ++i) {
        snake_body_update_coords(&snake->body[i], win);
        game_window_set_cell(win, snake->body[i].y, snake->body[i].x);
    }
}


static void snake_body_update_coords(snake_body_t* body, game_window_t* win)
{
    switch (body->dir) {
    case NORTH:
        --body->y;
        if (body->y == 0)
            body->y = win->lines - 2;
        break;
    case WEST:
        --body->x;
        if (body->x == 0)
            body->x = win->cols - 2;
        break;
    case SOUTH:
        ++body->y;
        if (body->y == win->lines - 1)
            body->y = 1;
        break;
    case EAST:
        ++body->x;
        if (body->x == win->cols - 1)
            body->x = 1;
        break;
    }
}


static inline snake_body_t snake_head(snake_t* snake)
{
    return snake->body[0];
}


static inline snake_body_t snake_tail(snake_t* snake)
{
    return snake->body[snake->length-1];
}
