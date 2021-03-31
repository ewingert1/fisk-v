#include <stdint.h>

#define GPIO_BASE 	0x40000100
#define GPIO_OUTPUTCFG	0b0000101100000000
#define GPIO_INPUTCFG	0b0000101100000000

#define GPIO_GPIO_ENABLE_OFFSET 0x90
#define GPIO_GPIO_OUTPUT_OFFSET 0x88

#define IRQ_CAUSE_BASE			16
#define IRQ_CAUSE_TIMER2		IRQ_CAUSE_BASE + 36

#define CLIC_HART0_ADDR			0x02800000
#define CLIC_INTIE				0x400

#define TIMER_BASE 		0x4000a500
#define TCCR_REG		TIMER_BASE
#define TMR2_0_REG		TIMER_BASE + 0x10
#define TMR2_1_REG		TIMER_BASE + 0x14
#define TMR2_2_REG		TIMER_BASE + 0x18
#define TMR3_0_REG		TIMER_BASE + 0x1C
#define TMR3_1_REG		TIMER_BASE + 0x20
#define TMR3_2_REG		TIMER_BASE + 0x24

#define TCR2_REG		TIMER_BASE + 0x2C
#define TCR3_REG		TIMER_BASE + 0x30
#define TMSR2_REG		TIMER_BASE + 0x34
#define TMSR3_REG		TIMER_BASE + 0x38

#define TIER2_REG		TIMER_BASE + 0x44
#define TIER3_REG		TIMER_BASE + 0x48

#define TPLVR2_REG		TIMER_BASE + 0x50
#define TPLCR2_REG		TIMER_BASE + 0x5C

#define TICR2_REG		TIMER_BASE + 0x78
#define TICR3_REG		TIMER_BASE + 0x7C

#define TCER_REG		TIMER_BASE + 0x84
#define TCMR_REG		TIMER_BASE + 0x88

void gpio11_toggle()
{
	*((uint32_t*)(GPIO_BASE+0x88)) = *((uint32_t*)(GPIO_BASE+0x88)) ^ (1 << 11);
}

__attribute__((naked))
void bl602_irq_handler()
{
	// gpio11_toggle();
	*((uint32_t*)(GPIO_BASE+0x88)) = *((uint32_t*)(GPIO_BASE+0x88)) ^ (1 << 11);
	*((uint32_t*)TICR2_REG) = 0b111;
}


void gpio11_init()
{
	uint32_t gpio11_cfg = 0b00001011000000000000000000000000;

	/* gpio mode on gpio11 */
	*((uint32_t*)(GPIO_BASE+0x14)) = gpio11_cfg;
	/* output enable on gpio11 */
	*((uint32_t*)(GPIO_BASE+0x90)) = 1 << 11;
	*((uint32_t*)(GPIO_BASE+0x88)) = 1 << 11;
}

void timer_init()
{
	/* enable toutes les clocks */
	*((uint32_t*)(0x40000000)) |= 0b1111;
	/* enable clock pour timer */
	*((uint32_t*)(0x40000024)) |= ((1 << 0x15) | 1) ;

	/* timer interruption enable in the clic */
	*(volatile uint8_t*)(CLIC_HART0_ADDR + CLIC_INTIE + IRQ_CAUSE_TIMER2) = 1;
	*(volatile uint8_t*)(CLIC_HART0_ADDR + CLIC_INTIE + IRQ_CAUSE_TIMER2 + 1) = 1;

	/* count disable pour timer2 */
	*((uint32_t*)TCER_REG) &= (~0b10);
	/* clock 1kHz pour timer2 et timer3 */
	*((uint32_t*)TCCR_REG) &= (~0b1100);
	*((uint32_t*)TCCR_REG) = 0b1000;
	/* match with 1000 => T=1s a peu pres */
	*((uint32_t*)TMR2_0_REG) = 1000;
	/* timer2 valeur par defaut 0 */
	*((uint32_t*)TPLVR2_REG) = 0;
	/* timer2 preload a comparer avec match register 0 */
	*((uint32_t*)TPLCR2_REG) &= (~0b11);
	*((uint32_t*)TPLCR2_REG) |= 1;
	/* preload pour timer2 => ca compte de 0 à match reg0 => interrupt puis compteur = match reg0*/
	*((uint32_t*)TCMR_REG) = 0;
	/* enable interrupt on timer2 with match register 0 */
	*((uint32_t*)TIER2_REG) &= (~0b111);
	*((uint32_t*)TIER2_REG) |= 1;
	/* count enable pour timer2 */
	*((uint32_t*)TCER_REG) |= 0b10;
}

void bl602_main()
{
	gpio11_init();
	timer_init();
	while(1)
	{
		if ( *((uint32_t*)TCR2_REG) >= 500 )
		{
			gpio11_toggle();
		} 
	}
}
