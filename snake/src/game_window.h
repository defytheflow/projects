#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "game_window.h"

#include <ncurses.h>
#include <stdbool.h>


typedef struct {
    int lines;
    int cols;
    char** cells;
    WINDOW* frame;
} game_window_t;


int game_window_init(game_window_t*, int lines, int cols);
void game_window_free(game_window_t*);
bool game_window_cell_empty(const game_window_t*, int y, int x);
void game_window_occupy_cell(game_window_t*, int y, int x);

#endif /* GAME_WINDOW_H */
