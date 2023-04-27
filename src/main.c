#include <stdio.h>
#include <math.h>

#include "main.h"
#include "util/system.h"
#include "util/getch.h"
#include "graphics/render.h"
#include "graphics/shapes.h"

static char pressed_key = 0;

#define RAY_START_X START_X
#define RAY_START_Y START_Y
#define RAY_END_X END_X
#define RAY_END_Y END_Y

uint8_t map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};

static int8_t player_x = RAY_START_X + 4;
static int8_t player_y = RAY_START_X + 8;

void draw_player(void)
{
    buffer_write(player_x, player_y, 'O', YELLOW);
}

void game_loop(void)
{
    buffer_clear();
    display_clear();

    if (pressed_key)
    {
        buffer_write(0, 3, pressed_key, CYAN);
        if (pressed_key == 'w')
        {
            player_y++;
        }
        if (pressed_key == 's')
        {
            player_y--;
        }
        if (pressed_key == 'd')
        {
            player_x++;
        }
        if (pressed_key == 'a')
        {
            player_x--;
        }

        pressed_key = 0;
    }

    buffer_write(START_X, START_Y, 'T', BLUE);
    draw_player();
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
