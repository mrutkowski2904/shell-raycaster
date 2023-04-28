#ifndef SHAPES_H
#define SHAPES_H

#include <stdint.h>

#define PI 3.1415

void draw_line(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y, uint8_t color);

/* +----------(x2,y2)
 * |              |
 * |              |
 * (x1,y1)--------+
 */
void draw_rectangle_2point(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color, uint8_t fill);
void rotate_point(int16_t *src_x, int16_t *src_y, int16_t pivot_x, int16_t pivot_y, float angle);

#endif
