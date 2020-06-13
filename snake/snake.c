#include "snake.h"
#include "game_window.h"
#include "keys.h"

#include <ncurses.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


static void snake_update_direction(snake_t*, int key);
static void snake_update_yx(snake_t*, game_window_t*);
static void snake_handle_border_collision(snake_t*, game_window_t*);


void snake_init(snake_t* snake, game_window_t* game_win, int capacity, int y, int x, char skin)
{
    snake->capacity = capacity;
    snake->length = 1;
    snake->skin = skin;

    snake->body = (snake_body_t*) malloc(sizeof(snake_body_t) * capacity);
    assert(snake->body != NULL);

    snake->body[0].y = y;
    snake->body[0].x = x;
    snake->body[0].dir = (direction_t) rand() % 4;

    game_win->cells[y][x] = skin;
}


void snake_free(snake_t* snake)
{
    free(snake->body);
}


snake_body_t snake_head(snake_t* snake)
{
    return snake->body[0];
}


snake_body_t snake_tail(snake_t* snake)
{
    return snake->body[snake->length - 1];
}


void snake_draw(snake_t* snake, game_window_t* game_win)
{
    for (int i = 0; i < snake->length; ++i)
        mvwaddch(game_win->frame, snake->body[i].y, snake->body[i].x, snake->skin);
}

const char* direction_to_str(direction_t dir)
{
    switch (dir) {
        case NORTH:
            return "north";
        case WEST:
            return "west";
        case SOUTH:
            return "south";
        case EAST:
            return "east";
    }
}

bool snake_grow(snake_t* snake)
{
    if (snake->length == snake->capacity)
        return false;

    int x, y;
    switch (snake_head(snake).dir) {
    case NORTH:
        y = snake_tail(snake).y + 1;
        x = snake_tail(snake).x;
        break;
    case WEST:
        y = snake_tail(snake).y;
        x = snake_tail(snake).x + 1;
        break;
    case SOUTH:
        y = snake_tail(snake).y - 1;
        x = snake_tail(snake).x;
        break;
    case EAST:
        y = snake_tail(snake).y;
        x = snake_tail(snake).x - 1;
        break;
    }

    snake->body[snake->length].y = y;
    snake->body[snake->length].x = x;
    snake->body[snake->length].dir = snake_tail(snake).dir;

    ++snake->length;
    return true;
}


void snake_move(snake_t* snake, game_window_t* game_win, int key)
{
    /* mvprintw(10, 1, "snake head %d %d %s\n", snake_head(snake).x, snake_head(snake).y, direction_to_str(snake_head(snake).dir)); */
    /* mvprintw(11, 1, "snake tail %d %d %s\n", snake_tail(snake).x, snake_tail(snake).y, direction_to_str(snake_tail(snake).dir)); */
    snake_update_direction(snake, key);
    snake_update_yx(snake, game_win);
}


static void snake_update_direction(snake_t* snake, int key)
{

    /* mvprintw(0, 1, "%d) %s\n", 0, direction_to_str(snake_head(snake).dir)); */
    for (int i = snake->length - 1; i > 0; --i) {
        snake->body[i].dir = snake->body[i-1].dir;
        /* mvprintw(i, 1, "%d) %s\n", i, direction_to_str(snake->body[i].dir)); */
    }
    /* for (int i = 1; i < snake->length; ++i) { */
    /*     snake->body[i].dir = snake->body[i-1].dir; */
    /*     mvprintw(i, 1, "%d) %s\n", i, direction_to_str(snake->body[i].dir)); */
    /* } */

    switch (key) {
    case _KEY_UP:
        if (snake_head(snake).dir != SOUTH)
            snake->body[0].dir = NORTH;
        break;
    case _KEY_LEFT:
        if (snake_head(snake).dir != EAST)
            snake->body[0].dir = WEST;
        break;
    case _KEY_DOWN:
        if (snake_head(snake).dir != NORTH)
            snake->body[0].dir = SOUTH;
        break;
    case _KEY_RIGHT:
        if (snake_head(snake).dir != WEST)
            snake->body[0].dir = EAST;
        break;
    }

    /* for (int i = 1; i < snake->length; ++i) */
    /*     snake->body[i].dir = snake->body[i-1].dir; */
}


static void snake_update_yx(snake_t* snake, game_window_t* game_win)
{
    for (int i = 0; i < snake->length; ++i)
        switch (snake->body[i].dir) {
        case NORTH:
            --snake->body[i].y;
            break;
        case WEST:
            --snake->body[i].x;
            break;
        case SOUTH:
            ++snake->body[i].y;
            break;
        case EAST:
            ++snake->body[i].x;
            break;
        }

    /* snake_handle_border_collision(snake, game_win); */
    /* for (int i = 0; i < snake->length; ++i) */
    /*     game_win->cells[snake->body[i].y][snake->body[i].x] = snake->skin; */
}


static void snake_handle_border_collision(snake_t* snake, game_window_t* game_win)
{
    if (snake_head(snake).x == 0) {
        snake->body[0].x = game_win->cols - 1;
    }

    else if (snake_head(snake).x == game_win->cols - 1) {
        snake->body[0].x = 1;
    }

    else if (snake_head(snake).y == 0) {
        snake->body[0].y = game_win->lines - 1;
    }

    else if (snake_head(snake).y == game_win->lines - 1) {
        snake->body[0].y = 1;
    }
}
