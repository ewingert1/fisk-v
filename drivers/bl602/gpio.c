#include "defs.h"
#include "gpio.h"

#define PINMODE_GPIO 11

void gpio_init(int id, gpio_direction_t dir, gpio_pull_t pull)
{
    uint32_t value;
    uint8_t reg_offset; /* register to use => 0 to 14 */
    uint8_t pin_offset; /* pin position in register => 0 or 1 */

    if(id > 28) return;
    if(id < 0) return;

    reg_offset = id/2;
    pin_offset = id%2;

    value = *(uint32_t*)(GPIO_BASE + (reg_offset*4));
    /* Clear current pin config */
    value &= ~(0xFFFF << (pin_offset*16));
    value |= (  ( (PINMODE_GPIO)        << 8) | 
                ( (pull == PULLDOWN)    << 5) |
                ( (pull == PULLUP)      << 4) |
                ( (dir  == INPUT)       << 0) ) << (pin_offset*16) ; 
    /* save configuration */
    *(uint32_t*)(GPIO_BASE + (reg_offset*4)) = value;

    if(dir == OUTPUT)
    {
        *(uint32_t*)(GPIO_OUTPUT_ENABLE) = (1 << id); 
    }
}

void gpio_output_toggle(int id)
{
    uint32_t value;
    
    if(id > 28) return;
    if(id < 0) return;

    value = *(uint32_t*)(GPIO_OUTPUT_LEVEL);
    value = value ^ (1 << id);
    *(uint32_t*)(GPIO_OUTPUT_LEVEL) = value;
}


