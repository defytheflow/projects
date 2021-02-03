#include "enemy.h"

#include "sprite.h"

#include <ncurses.h>

#include <time.h>
#include <stdlib.h>

static void put_random_xy(Sprite* s);

void enemy_init(Enemy* e, const char* skin_filename, int color_pair)
{
        put_random_xy(&e->sprite);
        e->sprite.color_pair = color_pair;
        e->vel = 1;
        // Initializes image, width and height
        sprite_load_image(&e->sprite, skin_filename);
}

void enemy_update(Enemy *e)
{
    sprite_clear(&e->sprite);
    if (e->sprite.y > LINES) {
        put_random_xy(&e->sprite);
    } else {
        e->sprite.y += e->vel;
    }
}

void enemy_del(Enemy* e)
{
        sprite_free_image(&e->sprite);
}

static void put_random_xy(Sprite* s)
{
        srand(time(NULL));
        s->x = rand() % (COLS - s->width) + 1;
        s->y = -s->height;
}