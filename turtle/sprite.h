#ifndef SPRITE_H
#define SPRITE_H

#include <ncurses.h>

typedef struct {
        int x;
        int y;
        int width;
        int height;
        int color_pair;
        char** image;
} Sprite;

void sprite_load_image(Sprite* s, const char* skin_filename);
void sprite_free_image(Sprite* s);
void sprite_draw(const Sprite* s);
void sprite_clear(const Sprite* s);

#endif