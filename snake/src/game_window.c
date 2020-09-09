#include "game_window.h"
#include "error.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_CELL 0
#define OCCUPIED_CELL 1


int game_window_init(game_window_t* win, int lines, int cols)
{
    if (LINES < lines || COLS < cols)
        return TERMINAL_SIZE_ERROR;

    win->lines = lines;
    win->cols = cols;
    win->frame = newwin(lines, cols, LINES / 2 - lines / 2, COLS / 2 - cols / 2);

    win->cells = (char**) malloc(lines * sizeof(char*));
    if (win->cells == NULL)
        return MEMORY_ALLOCATION_ERROR;

    for (int i = 0; i < lines; ++i) {
        win->cells[i] = (char*) malloc(cols);
        if (win->cells == NULL)
            return MEMORY_ALLOCATION_ERROR;
        memset(win->cells[i], 0, cols);
    }

    return SUCCESS;
}


void game_window_free(game_window_t* win)
{
    delwin(win->frame);
    for (int i = 0; i < win->lines; ++i) free(win->cells[i]);
    free(win->cells);
}


void game_window_occupy_cell(game_window_t* win, int y, int x)
{
    win->cells[y][x] = OCCUPIED_CELL;
}


bool game_window_cell_empty(const game_window_t* win, int y, int x)
{
    return win->cells[y][x] == EMPTY_CELL;
}
