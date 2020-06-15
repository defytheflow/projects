#include "snake.h"
#include "color.h"
#include "error.h"
#include "game_window.h"
#include "utils.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SNAKE_SKIN       '0'
#define SNAKE_MOVE_NORTH 'w'
#define SNAKE_MOVE_WEST  'a'
#define SNAKE_MOVE_SOUTH 's'
#define SNAKE_MOVE_EAST  'd'


static void snake_update_direction(snake_t*, int key);
static void snake_update_coords(snake_t*, game_window_t*);
static void snake_body_part_update_coords(snake_body_part_t* body, game_window_t* win);
static void snake_erase(const snake_t*, const game_window_t*);
static inline snake_body_part_t snake_head(snake_t* snake);
static inline snake_body_part_t snake_tail(snake_t* snake);


int snake_init(snake_t* snake, game_window_t* win)
{
    init_pair(SNAKE_COLOR, COLOR_GREEN, COLOR_BLACK);

    snake->capacity = (win->lines - 2) * (win->cols - 2);
    snake->length = 1;

    snake->body = (snake_body_part_t*) malloc(sizeof(snake_body_part_t) * snake->capacity);
    if (snake->body == NULL)
        return MEMORY_ALLOCATION_ERROR;

    snake->body[0].y = win->lines / 2;
    snake->body[0].x = win->cols / 2;
    snake->body[0].dir = (direction_t) random_range(0, 3);

    game_window_occupy_cell(win, snake->body[0].y, snake->body[0].x);

    return SUCCESS;
}


void snake_free(snake_t* snake)
{
    free(snake->body);
}


void snake_draw(const snake_t* snake, const game_window_t* win)
{
    wattron(win->frame, COLOR_PAIR(SNAKE_COLOR));
    for (int i = 0; i < snake->length; ++i)
        mvwaddch(win->frame, snake->body[i].y, snake->body[i].x, SNAKE_SKIN);
    wattroff(win->frame, COLOR_PAIR(SNAKE_COLOR));
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
        if (snake_head(snake).y == snake->body[i].y &&
            snake_head(snake).x == snake->body[i].x)
            return false;
    return true;
}


static void snake_update_direction(snake_t* snake, int key)
{
    for (int i = snake->length - 1; i > 0; --i)
        snake->body[i].dir = snake->body[i - 1].dir;

    switch (key) {
        case SNAKE_MOVE_NORTH:
            snake->body[0].dir = (snake_head(snake).dir != SOUTH) ? NORTH : SOUTH;
            break;
        case SNAKE_MOVE_WEST:
            snake->body[0].dir = (snake_head(snake).dir != EAST) ? WEST : EAST;
            break;
        case SNAKE_MOVE_SOUTH:
            snake->body[0].dir = (snake_head(snake).dir != NORTH) ? SOUTH : NORTH;
            break;
        case SNAKE_MOVE_EAST:
            snake->body[0].dir = (snake_head(snake).dir != WEST) ? EAST : WEST;
            break;
    }
}


static void snake_update_coords(snake_t* snake, game_window_t* win)
{
    snake_erase(snake, win);
    for (int i = 0; i < snake->length; ++i) {
        snake_body_part_update_coords(&snake->body[i], win);
        game_window_occupy_cell(win, snake->body[i].y, snake->body[i].x);
    }
}


static void snake_body_part_update_coords(snake_body_part_t* body, game_window_t* win)
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


static void snake_erase(const snake_t* snake, const game_window_t* win)
{
    for (int i = 0; i < snake->length; ++i)
        mvwaddch(win->frame, snake->body[i].y, snake->body[i].x, ' ');
}


static inline snake_body_part_t snake_head(snake_t* snake)
{
    return snake->body[0];
}


static inline snake_body_part_t snake_tail(snake_t* snake)
{
    return snake->body[snake->length - 1];
}
