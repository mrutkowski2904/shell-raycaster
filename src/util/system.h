#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

#define MS (1000U)
// #define LOOP_TIME_US (500 * MS)
#define LOOP_TIME_US (33 * MS)

void start_loop(void (*callback)(void), uint8_t join);

#endif