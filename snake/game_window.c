#include "game_window.h"

#include <ncurses.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CELL_EMPTY  0
#define CELL_FULL   1


void game_window_init(game_window_t* win, int lines, int cols, int y, int x)
{
    win->frame = newwin(lines, cols, y, x);
    win->lines = lines;
    win->cols = cols;
    win->cells = (char**) malloc(lines * sizeof(char*));
    assert(win->cells != NULL);

    for (int i = 0; i < lines; ++i) {
        win->cells[i] = (char*) malloc(cols);
        assert(win->cells[i] != NULL);
        memset(win->cells[i], 0, cols);
    }
}


void game_window_free(game_window_t* win)
{
    delwin(win->frame);
    for (int i = 0; i < win->lines; ++i)
        free(win->cells[i]);
    free(win->cells);
}


void game_window_refresh(game_window_t* win)
{
    box(win->frame, 0, 0);
    wrefresh(win->frame);
    wclear(win->frame);
}


void game_window_set_cell(game_window_t* win, int y, int x)
{
    win->cells[y][x] = CELL_FULL;
}


bool game_window_cell_empty(const game_window_t* win, int y, int x)
{
    return (win->cells[y][x] != CELL_EMPTY);
}
