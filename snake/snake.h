#ifndef SNAKE_H
#define SNAKE_H

#include "game_window.h"

#include <ncurses.h>
#include <stdbool.h>

typedef enum { NORTH, WEST, EAST, SOUTH } Direction;

typedef struct {
    int x, y;
    int capacity;
    int length;
    char* body;
    Direction dir;
} Snake;

void snake_init(Snake*, int capacity, int y, int x, Direction);
void snake_free(Snake*);
void snake_draw(Snake*, GameWindow*);
bool snake_grow_body(Snake*);
void snake_update_dir(Snake*, int key);
void snake_update_yx(Snake*, GameWindow*);

#endif /* SNAKE_H */
