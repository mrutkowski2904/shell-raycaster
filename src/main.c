#include <stdio.h>

#include "main.h"
#include "util/system.h"
#include "graphics/render.h"

void loop(void)
{
    static uint8_t direction = 1;
    static uint8_t pos_x = 0;
    buffer_clear();
    display_clear();

    if (direction)
    {
        pos_x++;
    }
    else
    {
        pos_x--;
    }

    if (pos_x == DISPLAY_X - 1)
    {
        direction = 0;
    }

    if (pos_x == 1)
    {
        direction = 1;
    }

    buffer_write(DISPLAY_X - pos_x, (DISPLAY_Y / 2) - 1, '*', YELLOW);
    buffer_write(pos_x, DISPLAY_Y / 2, '*', GREEN);
    buffer_write(DISPLAY_X - pos_x, (DISPLAY_Y / 2) + 1, '*', BLUE);

    buffer_write(0, 0, '*', CYAN);
    buffer_write(DISPLAY_X - 1, DISPLAY_Y - 1, '*', MAGENTA);
    buffer_draw();
}

int main(void)
{
    start_loop(loop);
    return 0;
}