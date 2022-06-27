#include <stdio.h>

#include "main.h"
#include "util/system.h"
#include "util/getch.h"
#include "graphics/render.h"
#include "graphics/shapes.h"

static char pressed_key = 0;

void game_loop(void)
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

    if (pressed_key)
    {
        buffer_write(0, 3, pressed_key, CYAN);
        pressed_key = 0;
    }

    draw_line(START_X, START_Y, END_X, END_Y, '*', WHITE);
    draw_line(START_X, END_Y - 3, END_X, (END_Y / 2) + 3, '*', YELLOW);
    draw_line(END_X, START_Y, START_X, END_Y, 'O', RED);
    draw_line(END_X / 2, START_Y, END_X / 2, END_Y, 'Y', BLUE);
    buffer_draw();
}

void keyboard_loop(void)
{
    char key;
    key = getch();
    if (!pressed_key)
    {
        pressed_key = key;
    }
}

int main(void)
{
    start_loop(game_loop, 0);
    start_loop(keyboard_loop, 1);
    return 0;
}