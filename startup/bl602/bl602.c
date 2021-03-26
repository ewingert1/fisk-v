#include <stdint.h>

#define GPIO_BASE 	0x40000100
#define GPIO_OUTPUTCFG	0b0000101100000000
#define GPIO_INPUTCFG	0b0000101100000000

#define GPIO_GPIO_ENABLE_OFFSET 0x90
#define GPIO_GPIO_OUTPUT_OFFSET 0x88




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

#define TICR2_REG		TIMER_BASE + 0x78
#define TICR3_REG		TIMER_BASE + 0x7C

#define TCER_REG		TIMER_BASE + 0x84
#define TCMR_REG		TIMER_BASE + 0x88


void bl602_irq_handler()
{


	*((uint32_t*)TICR2_REG) = 1;
}

void gpio11_toggle()
{
	*((uint32_t*)(GPIO_BASE+0x88)) = *((uint32_t*)(GPIO_BASE+0x88)) ^ (1 << 11);
}

void gpio11_init()
{
	uint32_t gpio11_cfg = 0b00001011000000000000000000000000;

	/* gpio mode on gpio11 */
	*((uint32_t*)(GPIO_BASE+0x14)) = gpio11_cfg;
	/* output enable on gpio11 */
	*((uint32_t*)(GPIO_BASE+0x90)) = 1 << 11;
}

void timer_init()
{
	/* clock 32k pour timer2 */
	*((uint32_t*)TCCR_REG) |= 0b0100;
	/* match with 32000 => T=1s a peu pres */
	*((uint32_t*)TMR2_0_REG) = 32000;
	/* enable interrupt on timer2 with match register 0 */
	*((uint32_t*)TIER2_REG) = 1;
	/* count enable pour timer2 */
	*((uint32_t*)TCER_REG) = 2;
	/* free run pour timer2 => ca compte de 0 à match reg0 => interrupt */
	*((uint32_t*)TCMR_REG) = 2;
}

void bl602_main()
{

}
