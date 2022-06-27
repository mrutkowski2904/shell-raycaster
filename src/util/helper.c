#include <stdint.h>

#include "util/helper.h"

void swap(uint8_t *a, uint8_t *b)
{
    uint8_t tmp = *a;
    *a = *b;
    *b = tmp;
}