#include "gpio.h"
#include "irq.h"
#include "timer.h"

void short_delay()
{
	for(int j=0; j<500000; j++);
}

void delay()
{
	for(int j=0; j<5000000; j++);
}

void __attribute__((interrupt)) systick()
{
	*(uint64_t*)(CLIC_MTIME) = 0;
	*(uint64_t*)(CLIC_MTIMECMP) = 12000000;
	// *(uint8_t*)(CLIC_HART0_INTIP + INT_CAUSE_MTIMER) = 0;
	*(uint32_t*)(GPIO_OUTPUT_LEVEL) = (*(uint32_t*)(GPIO_OUTPUT_LEVEL)) ^ (1 << 11);  
}

void bl602_main()
{
	init_irq();
	gpio_init(11, OUTPUT, PULLNONE);
	gpio_output_toggle(11);
	
	set_mtimer_interrupt();
	enable_irq(INT_CAUSE_MTIMER);
    CPU_ENABLE_IRQ();

	while(1);
}


