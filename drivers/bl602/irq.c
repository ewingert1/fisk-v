#include "defs.h"
#include "irq.h"

void init_irq()
{
    uint32_t ptr;

    /*clear mask*/
    for (ptr = CLIC_HART0_INTIE; ptr < CLIC_HART0_INTIE + 128; ptr++) {
        *(volatile uint8_t*)ptr = 0;
    }
    /*clear pending*/
    for (ptr = CLIC_HART0_INTIP; ptr < CLIC_HART0_INTIP + 128; ptr++) {
        *(volatile uint8_t*)ptr = 0;
    }
}

void enable_irq(int source)
{
    if (source > 128) return;
    if (source < 0) return;

	*(volatile uint8_t*)(CLIC_HART0_INTIE + source) = 1;
}

void disable_irq(int source)
{
    if (source > 128) return;
    if (source < 0) return;

	*(volatile uint8_t*)(CLIC_HART0_INTIE + source) = 0;
}

void trigger_swi()
{
	*(volatile uint8_t*)(CLIC_HART0_INTIP + INT_CAUSE_SWI) = 1;
}
