#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

#include <ncurses.h>

typedef struct {
        Sprite sprite;
        int vel;
} Enemy;

void enemy_init(Enemy* e, const char* skin_filename, int color_pair);
void enemy_update(Enemy *e);
void enemy_del(Enemy* e);

#endif