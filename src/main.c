#include <stdio.h>
#include <math.h>

#include "main.h"
#include "util/system.h"
#include "util/getch.h"
#include "graphics/render.h"
#include "graphics/shapes.h"

static char pressed_key = 0;

#define MAP_START_X START_X
#define MAP_START_Y START_Y
#define MAP_END_X ((END_X / 2) - 1)
#define MAP_END_Y END_Y

#define RAY_START_X ((END_X / 2) + 1)
#define RAY_START_Y START_Y
#define RAY_END_X END_X
#define RAY_END_Y END_Y

/*
 1,1,1,1,1,1,1,1,
   1,0,1,0,0,0,0,1,
   1,0,1,1,0,0,0,1,
   1,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,1,
   1,0,1,1,0,0,1,1,
   1,0,0,1,0,0,1,1,
   1,1,1,1,1,1,1,1,
   */

uint8_t map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};

void draw_map(void)
{
    uint8_t iter_x = 0;
    uint8_t iter_y = 0;

    for (uint8_t x = MAP_START_X; x < (8 * 2); x += 2)
    {
        for (uint8_t y = MAP_START_Y; y < (8 * 2); y += 2)
        {
            uint8_t data = map[iter_x][iter_y];

            buffer_write(x, y, '*', data ? BLUE : WHITE);
            buffer_write(x + 1, y, '*', data ? BLUE : WHITE);
            buffer_write(x, y + 1, '*', data ? BLUE : WHITE);
            buffer_write(x + 1, y + 1, '*', data ? BLUE : WHITE);
            iter_x++;
        }
        iter_x = 0;
        iter_y++;
    }
}

static int8_t player_x = MAP_START_X + 4;
static int8_t player_y = MAP_START_Y + 8;
static float player_angle = 0.0;
static float pdx = 0.0;
static float pdy = 0.0;

void draw_player(void)
{
    draw_line(player_x, player_y, player_x + pdx * 10.0, player_y + pdy * 10.0, '.', WHITE);
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
            // player_y++;
            player_x += pdx;
            player_y += pdy;
        }
        if (pressed_key == 's')
        {
            // player_y--;
            player_x -= pdx;
            player_y -= pdy;
        }

        if (pressed_key == 'd')
        {
            player_angle -= 0.5;
            if (player_angle < 0)
            {
                player_angle += 2 * PI;
            }
            pdx = cosf(player_angle) * 2;
            pdy = sinf(player_angle) * 2;

            // player_x++;
        }

        if (pressed_key == 'a')
        {
            // player_x--;
            player_angle += 0.5;
            if (player_angle > 2 * PI)
            {
                player_angle -= 2 * PI;
            }
            pdx = cosf(player_angle) * 2;
            pdy = sinf(player_angle) * 2;
        }

        pressed_key = 0;
    }

    draw_line((END_X / 2), START_Y, (END_X / 2), END_Y, '=', WHITE);
    draw_map();
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
