#ifndef FOOD_H
#define FOOD_H

#include "game_window.h"

typedef struct {
    int y;
    int x;
    char skin;
} food_t;

void food_init(food_t*, game_window_t*, char skin);
void food_draw(food_t*, game_window_t*);
void food_set_random_yx(food_t*, game_window_t*);

#endif /* FOOD_H */