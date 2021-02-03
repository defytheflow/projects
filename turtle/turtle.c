#include "turtle.h"
#include "colors.h"
#include "sprite.h"

#include <ncurses.h>

#include <stdlib.h>
#include <string.h>

static void turtle_handle_border_collision(Turtle* t);

/* Constructor. */
void turtle_init(Turtle* t, const char* skin_filename, int color_pair)
{
        t->sprite.x = COLS / 2 - 3;
        t->sprite.y = LINES - 10;
        t->sprite.width = 0; // TODO issue magic
        t->sprite.height = 1;
        t->sprite.color_pair = color_pair;
        t->vel = 2;
        // Initializes image, width and height
        sprite_load_image(&t->sprite, skin_filename);
}

void turtle_del(Turtle* t)
{
        sprite_free_image(&t->sprite);
}

void turtle_update(Turtle* t, int ch)
{
        switch (ch) {
        case 'h':
                sprite_clear(&t->sprite);
                t->sprite.x -= t->vel;
                break;
        case 'j':
                sprite_clear(&t->sprite);
                t->sprite.y += t->vel;
                break;
        case 'k':
                sprite_clear(&t->sprite);
                t->sprite.y -= t->vel;
                break;
        case 'l':
                sprite_clear(&t->sprite);
                t->sprite.x += t->vel;
                break;
        }
        turtle_handle_border_collision(t);
}

static void turtle_handle_border_collision(Turtle* t)
{
        // All minuses because of windows' borders
        if (t->sprite.x >= COLS - t->sprite.width - 1)
                t->sprite.x = COLS - t->sprite.width - 1;
        if (t->sprite.x <= 0)
                t->sprite.x = 1;
        if (t->sprite.y >= LINES - t->sprite.height - 1)
                t->sprite.y = LINES - t->sprite.height - 1;
        if (t->sprite.y <= 0)
                t->sprite.y = 1;
}
