#include <stdint.h>

#include "graphics/shapes.h"
#include "graphics/render.h"
#include "util/helper.h"

void draw_line(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint8_t value, uint8_t color)
{
    if (start_x > end_x)
    {
        swap(&start_x, &end_x);
        swap(&start_y, &end_y);
    }

    // horizontal line
    if (start_x == end_x)
    {
        if (start_y > end_y)
        {
            swap(&start_y, &end_y);
        }
        while (start_y <= end_y)
        {
            buffer_write(start_x, start_y, value, color);
            start_y++;
        }
    }

    int dy = (int)end_y - (int)start_y;
    int dx = (int)end_x - (int)start_x;

    float a = dy / (dx * 1.0);
    float b = (-1.0 * (int)start_x) + (int)start_y;
    uint8_t y;

    while (start_x <= end_x)
    {
        y = (uint8_t)(a * (int)start_x + b);
        buffer_write(start_x, y, value, color);
        start_x++;
    }
}