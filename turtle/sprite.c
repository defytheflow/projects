#include "sprite.h"

#include "colors.h"

#include <ncurses.h>

#include <stdlib.h>

void sprite_load_image(Sprite* s, const char* skin_filename)
{
        FILE* skin_file = fopen(skin_filename, "r");
        if (!skin_file) {
                fprintf(stderr, "Error: cannot open file %s.\n", skin_filename);
                exit(1);
        }

        int ch, length = 0;
        char temp_buffer[256];
        while ((ch = fgetc(skin_file)) != EOF) {
                if (ch == '\n') {
                        s->height += 1;
                        continue;
                }
                temp_buffer[length++] = ch;
        }
        s->width = length / s->height;

        s->image = malloc(sizeof(char*) * s->height);
        for (int i = 0; i < s->height; ++i) {
                s->image[i] = malloc(sizeof(char) * s->width);
        }

        int j = 0;
        for (int row = 0; row < s->height; ++row) {
                for (int col = 0; col < s->width; ++col) {
                        s->image[row][col] = temp_buffer[j++];
                }
        }
}

void sprite_free_image(Sprite* s)
{
        for (int i = 0; i < s->height; ++i) {
                free(s->image[i]);
        }
        free(s->image);
}

void sprite_draw(const Sprite* s)
{
        attron(COLOR_PAIR(s->color_pair));
        for (int i = 0; i < s->height; ++i) {
                for (int j = 0; j < s->width; ++j) {
                        mvaddch(s->y + i, s->x + j, s->image[i][j]);
                }
        }
        attroff(COLOR_PAIR(s->color_pair));
}

void sprite_clear(const Sprite* s)
{
        attron(COLOR_PAIR(BG_COLOR));
        for (int i = 0; i < s->height; ++i) {
                for (int j = 0; j < s->width; ++j) {
                        mvaddch(s->y + i, s->x + j, ' ');
                }
        }
        attroff(COLOR_PAIR(BG_COLOR));
}