#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

#define DISPLAY_WIDTH 120U
#define DISPLAY_HEIGHT 40U

#define START_X 0
#define END_X (DISPLAY_WIDTH - 1)
#define START_Y 0
#define END_Y (DISPLAY_HEIGHT - 1)

#define BLACK 0
#define WHITE 1
#define GRAY 2
#define BLUE 3
#define RED 4

void display_clear(void);
void buffer_write(int8_t x, int8_t y, uint8_t color);
void buffer_draw(void);
void buffer_clear(void);

#endif