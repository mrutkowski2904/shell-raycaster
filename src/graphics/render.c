#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "render.h"

static uint8_t display_buffer[DISPLAY_X][DISPLAY_Y] = {0};
static void handle_error(uint8_t err);

void display_clear(void)
{
    system("clear -x");
}

void buffer_write(uint8_t x, uint8_t y, uint8_t value)
{
    if ((x >= 0 && x < DISPLAY_X) && (y >= 0 && y < DISPLAY_Y))
    {
        display_buffer[x][y] = value;
    }
    else
    {
        handle_error(0);
    }
}

void buffer_draw(void)
{
    for (uint8_t y = 0; y < DISPLAY_Y; y++)
    {
        for (uint8_t x = 0; x < DISPLAY_X; x++)
        {
            uint8_t data = display_buffer[x][y];
            data ? printf("%c", (char)data) : printf(" ");
        }
        printf("\n");
    }
}

void buffer_clear(void)
{
    for (uint8_t y = 0; y < DISPLAY_Y; y++)
    {
        for (uint8_t x = 0; x < DISPLAY_X; x++)
        {
            display_buffer[x][y] = 0;
        }
    }
}

static void handle_error(uint8_t err)
{
    while (1)
    {
        printf("ERROR\r\n");
    }
}