#ifndef FOOD_H
#define FOOD_H

#include "game_window.h"

typedef struct {
    int y, x;
    char body;
} Food;

void food_init(Food*, GameWindow*);
void food_set_random_yx(Food*, GameWindow*);
void food_draw(Food*, GameWindow*);

#endif /* FOOD_H */
