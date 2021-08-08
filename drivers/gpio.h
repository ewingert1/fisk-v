#pragma once
#include <stdint.h>

typedef enum {
    OUTPUT  = 0,
    INPUT   = 1
} gpio_direction_t;

typedef enum {
    PULLNONE    = 0,
    PULLUP      = 1,
    PULLDOWN    = 2
} gpio_pull_t;


void gpio_init          (int id, gpio_direction_t dir, gpio_pull_t pull);
void gpio_output_toggle (int id);
