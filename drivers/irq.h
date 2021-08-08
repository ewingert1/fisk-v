#pragma once
#include <stdint.h>

#ifdef TARGET_BL602
#include "bl602/defs.h"
#define CPU_ENABLE_IRQ BL602_ENABLE_IRQ
#endif

void init_irq();
void enable_irq(int source);
void disable_irq(int source);

