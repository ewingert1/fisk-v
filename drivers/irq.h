#pragma once
#include <stdint.h>

#ifdef TARGET_BL602
#include "bl602/defs.h"
#define CPU_ENABLE_IRQ      BL602_ENABLE_IRQ
#define CPU_DISABLE_IRQ     BL602_DISABLE_IRQ
#define CPU_WAIT_IRQ        BL602_WAIT_IRQ
#endif

void init_irq();
void enable_irq(int source);
void disable_irq(int source);
void trigger_swi();
