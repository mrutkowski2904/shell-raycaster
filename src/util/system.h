#ifndef SYSTEM_H
#define SYSTEM_H

#define MS (1000U)
// #define LOOP_TIME_US (200 * MS)
#define LOOP_TIME_US (33 * MS)

void start_loop(void (*callback)(void));

#endif