#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "render.h"

static uint8_t display_buffer[DISPLAY_X][DISPLAY_Y] = {0};
static uint8_t color_buffer[DISPLAY_X][DISPLAY_Y] = {0};

static void draw_pixel(uint8_t value, uint8_t color);

void display_clear(void)
{
    system("clear -x");
}

void buffer_write(int8_t x, int8_t y, uint8_t value, uint8_t color)
{
    if ((x >= 0 && x < DISPLAY_X) && (y >= 0 && y < DISPLAY_Y))
    {
        display_buffer[x][DISPLAY_Y - y - 1] = value;
        color_buffer[x][DISPLAY_Y - y - 1] = color;
    }
}

void buffer_draw(void)
{
    for (uint8_t y = 0; y <= DISPLAY_Y + 1; y++)
    {
        for (uint8_t x = 0; x <= DISPLAY_X + 1; x++)
        {
            if (x == 0 || y == 0 || x == DISPLAY_X + 1 || y == DISPLAY_Y + 1)
            {
                printf("\033[1;47m \033[0m");
            }
            else
            {
                uint8_t value = display_buffer[x - 1][y - 1];
                uint8_t color = color_buffer[x - 1][y - 1];
                draw_pixel(value, color);
            }
        }
        printf("\n");
    }
}

void buffer_clear(void)
{
    memset(display_buffer, 0, DISPLAY_X * DISPLAY_Y * sizeof(uint8_t));
    memset(color_buffer, 0, DISPLAY_X * DISPLAY_Y * sizeof(uint8_t));
}

static void draw_pixel(uint8_t value, uint8_t color)
{
    if (value)
    {
        switch (color)
        {
        case RED:
            printf("\033[1;31m%c\033[0m", (char)value);
            break;
        case GREEN:
            printf("\033[1;32m%c\033[0m", (char)value);
            break;
        case YELLOW:
            printf("\033[1;33m%c\033[0m", (char)value);
            break;
        case BLUE:
            printf("\033[1;34m%c\033[0m", (char)value);
            break;
        case MAGENTA:
            printf("\033[1;35m%c\033[0m", (char)value);
            break;
        case CYAN:
            printf("\033[1;36m%c\033[0m", (char)value);
            break;
        default:
            printf("%c", (char)value);
            break;
        }
    }
    else
    {
        printf(" ");
    }
}