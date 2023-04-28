#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#include "main.h"
#include "util/system.h"
#include "util/getch.h"
#include "graphics/render.h"
#include "graphics/shapes.h"

#define MOVE_SPEED 1.0
#define ROTATION_SPEED 0.2

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

uint8_t map[MAP_WIDTH][MAP_HEIGHT] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

float position_x = 1, position_y = 1;
float direction_x = -1, direction_y = 0;
float cam_plane_x = 0, cam_plane_y = 0.66;

static char pressed_key = 0;

void game_loop(void)
{
  buffer_clear();
  display_clear();

  buffer_write(START_X, START_Y, 'S', WHITE);
  buffer_write(END_X, END_Y, 'E', WHITE);

  for (int x = 0; x < DISPLAY_WIDTH; x++)
  {
    // continue;
    float cam_plane_fraction = 2 * x / (float)DISPLAY_WIDTH - 1;
    float ray_direction_x = direction_x + cam_plane_x * cam_plane_fraction;
    float ray_direction_y = direction_y + cam_plane_y * cam_plane_fraction;

    // current box that the player is in
    int map_box_x = (int)position_x;
    int map_box_y = (int)position_y;

    // ray length from player position to the next x or y side of the map box
    float side_distance_x, side_distance_y;

    // ray length from x or y side to the next x or y-side
    float delta_distance_x = (ray_direction_x == 0) ? FLT_MAX : fabsf(1 / ray_direction_x);
    float delta_distance_y = (ray_direction_y == 0) ? FLT_MAX : fabsf(1 / ray_direction_y);

    int step_x, step_y;
    bool hit = false;
    int side;

    // initial step and distance from current player position to the first x or y side
    if (ray_direction_x < 0)
    {
      step_x = -1;
      side_distance_x = (position_x - map_box_x) * delta_distance_x;
    }
    else
    {
      step_x = 1;
      side_distance_x = (map_box_x + 1.0 - position_x) * delta_distance_x;
    }

    if (ray_direction_y < 0)
    {
      step_y = -1;
      side_distance_y = (position_y - map_box_y) * delta_distance_y;
    }
    else
    {
      step_y = 1;
      side_distance_y = (map_box_y + 1.0 - position_y) * delta_distance_y;
    }

    // use DDA alghoritm to trace ray until it hits a wall
    while (hit == false)
    {
      if (side_distance_x < side_distance_y)
      {
        side_distance_x += delta_distance_x;
        map_box_x += step_x;
        side = 0;
      }
      else
      {
        side_distance_y += delta_distance_y;
        map_box_y += step_y;
        side = 1;
      }

      if (map[map_box_x][map_box_y] != 0)
        hit = true;
    }

    // calculate length of the ray that hit the wall
    // this is the distance to the camera plane - not the player position
    // (to eliminate fish eye effect)
    float wall_distance;
    if (side == 0)
      wall_distance = side_distance_x - delta_distance_x;
    else
      wall_distance = side_distance_y - delta_distance_y;

    int line_height = (int)(DISPLAY_HEIGHT / wall_distance);

    int line_start = (-line_height / 2) + (DISPLAY_HEIGHT / 2);

    if (line_start < 0)
      line_start = 0;

    int line_end = (line_height / 2) + (DISPLAY_HEIGHT / 2);
    if (line_end >= DISPLAY_HEIGHT)
      line_end = DISPLAY_HEIGHT - 1;

    char symbol = '*';

    if (side == 1)
      symbol = '.';

    draw_line(x, line_start, x, line_end, symbol, WHITE);
  }

  if (pressed_key)
  {
    buffer_write(0, 3, pressed_key, CYAN);
    if (pressed_key == 'w')
    {
      if (map[(int)(position_x + direction_x * MOVE_SPEED)][(int)position_y] == 0)
        position_x += direction_x * MOVE_SPEED;

      if (map[(int)(position_x)][(int)(position_y + direction_y * MOVE_SPEED)] == 0)
        position_y += direction_y * MOVE_SPEED;
    }
    if (pressed_key == 's')
    {
      if (map[(int)(position_x - direction_x * MOVE_SPEED)][(int)position_y] == 0)
        position_x -= direction_x * MOVE_SPEED;

      if (map[(int)(position_x)][(int)(position_y - direction_y * MOVE_SPEED)] == 0)
        position_y -= direction_y * MOVE_SPEED;
    }

    // direction and camera plane must be rotated
    if (pressed_key == 'd')
    {
      float old_direction_x = direction_x;
      direction_x = direction_x * cosf(-ROTATION_SPEED) - direction_y * sinf(-ROTATION_SPEED);
      direction_y = old_direction_x * sinf(-ROTATION_SPEED) + direction_y * cosf(-ROTATION_SPEED);

      float old_cam_plane_x = cam_plane_x;
      cam_plane_x = cam_plane_x * cosf(-ROTATION_SPEED) - cam_plane_y * sinf(-ROTATION_SPEED);
      cam_plane_y = old_cam_plane_x * sinf(-ROTATION_SPEED) + cam_plane_y * cosf(-ROTATION_SPEED);
    }
    if (pressed_key == 'a')
    {
      float old_direction_x = direction_x;
      direction_x = direction_x * cosf(ROTATION_SPEED) - direction_y * sinf(ROTATION_SPEED);
      direction_y = old_direction_x * sinf(ROTATION_SPEED) + direction_y * cosf(ROTATION_SPEED);

      float old_cam_plane_x = cam_plane_x;
      cam_plane_x = cam_plane_x * cosf(ROTATION_SPEED) - cam_plane_y * sinf(ROTATION_SPEED);
      cam_plane_y = old_cam_plane_x * sinf(ROTATION_SPEED) + cam_plane_y * cosf(ROTATION_SPEED);
    }

    pressed_key = 0;
  }

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
