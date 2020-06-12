#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "game_window.h"

#include <ncurses.h>
#include <stdbool.h>

typedef struct {
    WINDOW* frame;
    char** cells;
    int lines, cols;
} GameWindow;

void game_window_init(GameWindow*, int lines, int cols, int y, int x);
void game_window_free(GameWindow*);
void game_window_refresh(GameWindow*);
bool yx_collides_with_border(GameWindow*, int y, int x);
bool yx_occupied(GameWindow*, int y, int x);

#endif /* GAME_WINDOW_H */
