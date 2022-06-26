#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#include "system.h"

static void *loop(void *data)
{
    void (*callback)(void) = data;
    while (1)
    {
        if (callback != NULL)
        {
            callback();
        }
        usleep(LOOP_TIME_US);
    }
    return 0;
}

void start_loop(void (*callback)(void))
{
    pthread_t loop_thread;
    pthread_create(&loop_thread, NULL, loop, callback);
    pthread_join(loop_thread, NULL);
}