#ifndef TURTLE_H
#define TURTLE_H

#include "sprite.h"

#include <ncurses.h>

typedef struct {
        Sprite sprite;
        int vel;
} Turtle;

void turtle_init(Turtle* t, const char* skin_filename, int color_pair);
void turtle_del(Turtle* t);
void turtle_update(Turtle* t, int ch);

#endif
