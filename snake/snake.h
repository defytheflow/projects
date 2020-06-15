#ifndef SNAKE_H
#define SNAKE_H

#include "game_window.h"

#include <ncurses.h>
#include <stdbool.h>


typedef enum {
    NORTH,
    WEST,
    EAST,
    SOUTH,
} direction_t;


typedef struct {
    int y;
    int x;
    direction_t dir;
} snake_body_part_t;


typedef struct {
    int capacity;
    int length;
    snake_body_part_t* body;
} snake_t;


int snake_init(snake_t*, game_window_t*);
void snake_free(snake_t*);
void snake_draw(const snake_t*, const game_window_t*);
bool snake_grow(snake_t*);
bool snake_move(snake_t*, game_window_t*, int key);

#endif /* SNAKE_H */
