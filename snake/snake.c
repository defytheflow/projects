#include <ncurses.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define _KEY_UP     'w'
#define _KEY_LEFT   'a'
#define _KEY_DOWN   's'
#define _KEY_RIGHT  'd'
#define _KEY_QUIT   'q'

#define GAME_WIN_X       0
#define GAME_WIN_Y       0
#define GAME_WIN_LINES   LINES / 2
#define GAME_WIN_COLS    COLS / 3 * 2

#define SCORE_WIN_X      GAME_WIN_COLS
#define SCORE_WIN_Y      GAME_WIN_Y
#define SCORE_WIN_LINES  GAME_WIN_LINES
#define SCORE_WIN_COLS   COLS - GAME_WIN_COLS
#define SCORE_LBL_X      2
#define SCORE_LBL_Y      1

#define SNAKE_HEAD        'O'
#define SNAKE_DIRECTION   NORTH
#define SNAKE_BODY        'o'
#define SNAKE_MAX_BODY    256
#define SNAKE_EMPTY_BODY  '\0'
#define SNAKE_X           GAME_WIN_COLS / 2
#define SNAKE_Y           GAME_WIN_LINES / 2

typedef enum { NORTH, WEST, EAST, SOUTH } Direction;

typedef struct {
    int x, y;
    char head;
    char body[SNAKE_MAX_BODY];
    Direction dir;
} Snake;

void snake_init(Snake*s);
void snake_update_direction(Snake*, int);
void snake_update_xy(Snake*);
void snake_print(Snake*, WINDOW*);

void setup_ncurses(void);
void clean_up(void);

WINDOW *game_win, *score_win;

int main(void)
{
    setup_ncurses();

    game_win = newwin(GAME_WIN_LINES, GAME_WIN_COLS, GAME_WIN_Y, GAME_WIN_X);

    score_win = newwin(SCORE_WIN_LINES, SCORE_WIN_COLS, SCORE_WIN_Y, SCORE_WIN_X);
    box(score_win, 0, 0);

    Snake snake;
    snake_init(&snake);

    int c;
    while ((c = getch()) != _KEY_QUIT) {
        snake_update_direction(&snake, c);
        snake_update_xy(&snake);
        snake_print(&snake, game_win);
        box(game_win, 0, 0);
        wrefresh(game_win);
        wrefresh(score_win);
    }

    clean_up();

    return 0;
}

void setup_ncurses(void)
{
    initscr();
    noecho();
    curs_set(0);
    halfdelay(1);
}

void clean_up(void)
{
    delwin(game_win);
    delwin(score_win);
    endwin();
}

void snake_init(Snake* snake)
{
    snake->x = SNAKE_X;
    snake->y = SNAKE_Y;
    snake->dir = SNAKE_DIRECTION;
    snake->head = SNAKE_HEAD;
    memset(snake->body, SNAKE_EMPTY_BODY, SNAKE_MAX_BODY);
}

/*
 * Updates snake's direction based on a key pressed.
 */
void snake_update_direction(Snake* snake, int key)
{
    switch (key) {
    case _KEY_UP:
        snake->dir = NORTH;
        break;
    case _KEY_LEFT:
        snake->dir = WEST;
        break;
    case _KEY_DOWN:
        snake->dir = SOUTH;
        break;
    case _KEY_RIGHT:
        snake->dir = EAST;
        break;
    }
}

/*
 * Increments/decrements snake's x or y based on it's direction.
 */
void snake_update_xy(Snake* snake)
{
    switch (snake->dir) {
    case NORTH:
        --snake->y;
        break;
    case WEST:
        --snake->x;
        break;
    case SOUTH:
        ++snake->y;
        break;
    case EAST:
        ++snake->x;
        break;
    }
}

void snake_print(Snake* snake, WINDOW* win)
{
    wclear(win);
    mvwaddch(win, snake->y, snake->x, snake->head);
}
