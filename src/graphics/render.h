#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

#define DISPLAY_X 40U
#define DISPLAY_Y 20U

void display_clear(void);
void buffer_write(uint8_t x, uint8_t y, uint8_t value);
void buffer_draw(void);
void buffer_clear(void);

#endif