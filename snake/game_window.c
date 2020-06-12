#include "game_window.h"

#include <ncurses.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void game_window_init(GameWindow* game_win, int lines, int cols, int y, int x)
{
    game_win->frame = newwin(lines, cols, y, x);
    game_win->lines = lines;
    game_win->cols = cols;
    game_win->cells = (char**) malloc(lines * sizeof(char*));
    assert(game_win->cells != NULL);

    for (int i = 0; i < lines; ++i) {
        game_win->cells[i] = (char*) malloc(cols);
        assert(game_win->cells[i] != NULL);
        memset(game_win->cells[i], 0, cols);
    }
}


void game_window_free(GameWindow* game_win)
{
    delwin(game_win->frame);
    for (int i = 0; i < game_win->lines; ++i)
        free(game_win->cells[i]);
    free(game_win->cells);
}


void game_window_refresh(GameWindow* game_win)
{
    box(game_win->frame, 0, 0);
    wrefresh(game_win->frame);
    wclear(game_win->frame);
}

bool yx_collides_with_border(GameWindow* game_win, int y, int x)
{
    return (y == 0 || y == game_win->lines - 1 || x == 0 || x == game_win->cols - 1);
}

bool yx_occupied(GameWindow* game_win, int y, int x)
{
    return (game_win->cells[y][x] != 0);
}
