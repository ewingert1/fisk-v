#include "gpio.h"
#include "irq.h"
#include "timer.h"

void bl602_main()
{
	uint32_t* hbn_base 	= (uint32_t*)0x4000F000;
	uint32_t* hbn_clk 	= (uint32_t*)0x4000F030;

	init_irq();
	gpio_init(11, OUTPUT, PULLNONE);
	gpio_output_toggle(11);
	
	// timer_init();


	// uint32_t val;
	// /* RTC TOGGLE */

	// val = *hbn_clk;
	// /* clear clock 32k */
	// val &= 0xFFFFFFE7;
	// /* clock 32k = xtal */
	// val |= (1 << 3);
	// *hbn_clk = val;

	set_mtimer_interrupt();
    CPU_ENABLE_IRQ();

	// /* enable toutes les clocks */
	// *((volatile uint32_t*)(0x40000000)) |= 0b1111;
	// (*hbn_base) |= 0x01; // activer la clock

	while(1);
}

// void bl602_main()
// {
// 	init_irq();
// 	gpio_init(11, OUTPUT, PULLNONE);

// 	while(1)
// 	{
// 		for(int j=0; j<500000; j++);
// 		gpio_output_toggle(11);
// 	}

// 	while(1);
// }

