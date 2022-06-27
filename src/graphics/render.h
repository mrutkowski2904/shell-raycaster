#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

#define DISPLAY_X 50U
#define DISPLAY_Y 20U

#define START_X 0
#define END_X (DISPLAY_X - 1)
#define START_Y 0
#define END_Y (DISPLAY_Y - 1)

#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define MAGENTA 5
#define CYAN 6

void display_clear(void);
void buffer_write(uint8_t x, uint8_t y, uint8_t value, uint8_t color);
void buffer_draw(void);
void buffer_clear(void);

#endif