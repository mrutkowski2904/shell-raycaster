#include <stdint.h>
#include <math.h>

#include "graphics/shapes.h"
#include "graphics/render.h"
#include "util/helper.h"

void draw_line(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y, uint8_t color)
{
    if (start_x > end_x)
    {
        swap((char *)&start_x, (char *)&end_x);
        swap((char *)&start_y, (char *)&end_y);
    }

    // horizontal line
    if (start_x == end_x)
    {
        if (start_y > end_y)
        {
            swap((char *)&start_y, (char *)&end_y);
        }
        while (start_y < end_y)
        {
            buffer_write(start_x, start_y, color);
            start_y++;
        }
    }

    // vertical line
    if (start_y == end_y)
    {
        while (start_x <= end_x)
        {
            buffer_write(start_x, start_y, color);
            start_x++;
        }
    }

    int dx = end_x - start_x;
    int dy = end_y - start_y;

    float a = dy / (dx * 1.0);
    float b = (-1.0 * start_x) + start_y;

    // int tmp = a * 3;
    // a = tmp / 3.0;

    // tmp = b * 3;
    // b = tmp / 3.0;

    int16_t y;

    while (start_x < end_x)
    {
        y = (a * start_x) + b;
        buffer_write(start_x, y, color);
        start_x++;
    }
}

void rotate_point(int16_t *src_x, int16_t *src_y, int16_t pivot_x, int16_t pivot_y, float angle)
{
    float new_x, new_y;
    float s = sinf(angle);
    float c = cosf(angle);

    *src_x -= pivot_x;
    *src_y -= pivot_y;

    new_x = ((*src_x) * c) - (pivot_y * s);
    new_y = ((*src_x) * s) + (pivot_y * c);

    *src_x = new_x + pivot_x;
    *src_y = new_y + pivot_y;
}

void draw_rectangle_2point(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color, uint8_t fill)
{
    int16_t ll_x = x1;
    int16_t ll_y = y1;

    int16_t lr_x = x2;
    int16_t lr_y = y1;

    int16_t ul_x = x1;
    int16_t ul_y = y2;

    int16_t ur_x = x2;
    int16_t ur_y = y2;

    draw_line(ll_x, ll_y, lr_x, lr_y, color);
    draw_line(ll_x, ll_y, ul_x, ul_y, color);

    draw_line(ul_x, ul_y, ur_x, ur_y, color);
    draw_line(ur_x, ur_y, lr_x, lr_y, color);

    if (fill)
    {
        int16_t start_x = MIN(x1, x2);
        int16_t end_x = MAX(x1, x2);

        int16_t start_y = MIN(y1, y2);
        int16_t end_y = MAX(y1, y2);

        for (int16_t x = start_x; x <= end_x; x++)
        {
            for (int16_t y = start_y; y <= end_y; y++)
            {
                buffer_write(x, y, color);
            }
        }
    }
}