#include <stdint.h>

#define GPIO_BASE 	0x40000100
#define GPIO_OUTPUTCFG	0b0000101100000000
#define GPIO_INPUTCFG	0b0000101100000000

#define GPIO_GPIO_ENABLE_OFFSET 0x90
#define GPIO_GPIO_OUTPUT_OFFSET 0x88

#define IRQ_CAUSE_BASE			16
#define IRQ_CAUSE_TIMER1		IRQ_CAUSE_BASE + 36
#define IRQ_CAUSE_TIMER2		IRQ_CAUSE_BASE + 37

#define CLINT_BASE_ADDR				0x02000000
#define CLIC_MTIME          		0xBFF8

#define CLIC_HART0_ADDR				0x02800000
#define CLIC_HART0_INTIP_ADDR		0x02800000
#define CLIC_HART0_INTIE_ADDR		0x02800400

#define CLIC_INTIE		0x400


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

#define TILR2_REG		TIMER_BASE + 0x90
#define TILR3_REG		TIMER_BASE + 0x94

#define TCVWR2_REG		TIMER_BASE + 0xA8
#define TCVWR3_REG		TIMER_BASE + 0xAC

#define TCVSYN2_REG		TIMER_BASE + 0xB4
#define TCDR_REG		TIMER_BASE + 0xBC

/* ******************************************************* */
/* Stuff copied from bl_iot_sdk to understand what's wrong */
#define configCPU_CLOCK_HZ              ( 10 * 1000 * 1000 ) /*QEMU*/
#define configTICK_RATE_HZ              ( ( uint32_t ) 1000 )
#define configCLIC_TIMER_ENABLE_ADDRESS     (0x02800407)
uint64_t ullNextTime = 0ULL;
const uint64_t *pullNextTime = &ullNextTime;
uint32_t uxTimerIncrementsForOneTick = ( uint32_t ) 1; //( configCPU_CLOCK_HZ / configTICK_RATE_HZ ); /* Assumes increment won't go over 32-bits. */
volatile uint64_t * const pullMachineTimerCompareRegister = ( volatile uint64_t * const ) ( CLINT_BASE_ADDR + 0x4000 );
/* ******************************************************* */

void vPortSetupTimerInterrupt( void )
{
uint32_t ulCurrentTimeHigh, ulCurrentTimeLow;
volatile uint32_t * const pulTimeHigh = ( volatile uint32_t * const ) ( CLINT_BASE_ADDR + 0xBFFC );
volatile uint32_t * const pulTimeLow = ( volatile uint32_t * const ) ( CLINT_BASE_ADDR + 0xBFF8 );

	do
	{
		ulCurrentTimeHigh = *pulTimeHigh;
		ulCurrentTimeLow = *pulTimeLow;
	} while( ulCurrentTimeHigh != *pulTimeHigh );

	ullNextTime = ( uint64_t ) ulCurrentTimeHigh;
	ullNextTime <<= 32ULL;
	ullNextTime |= ( uint64_t ) ulCurrentTimeLow;
	ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;
	*pullMachineTimerCompareRegister = ullNextTime;

	/* Prepare the time to use after the next tick interrupt. */
	ullNextTime += ( uint64_t ) uxTimerIncrementsForOneTick;

	/* Enable software interrupts */
	// *(volatile uint8_t*)(CLIC_HART0_INTIE_ADDR+3) = 1;
	/* Trigger a software interrupt */
	// *(volatile uint8_t*)(CLIC_HART0_INTIP_ADDR+3) = 1;

	/* Enable mtimer interrupt */
    // *(volatile uint8_t*)configCLIC_TIMER_ENABLE_ADDRESS = 1;
}


void gpio11_toggle()
{
	*((uint32_t*)(GPIO_BASE+0x88)) = *((uint32_t*)(GPIO_BASE+0x88)) ^ (1 << 11);
}

__attribute__((naked))
void bl602_irq_handler(void)
{
	// gpio11_toggle();
	// Clear gpio 11
	*((uint32_t*)(GPIO_BASE+0x88)) &= (~(1 << 11));
	__asm volatile( "mret" );
}

void bl_irq_init(void)
{
	/* ******************************************************* */
	/* Stuff copied from bl_iot_sdk to understand what's wrong */

    uint32_t ptr;
    uint32_t tmpVal;

    /*clear mask*/
    for (ptr = 0x02800400; ptr < 0x02800400 + 128; ptr++) {
        *(uint8_t*)ptr = 0;
    }
    /*clear pending*/
    for (ptr = 0x02800000; ptr < 0x02800000 + 128; ptr++) {
        *(uint8_t*)ptr = 0;
    }
	/* ******************************************************* */
}

void gpio11_init()
{
	uint32_t gpio11_cfg = 0b00001011000000000000000000000000;

	/* gpio mode on gpio11 */
	*((uint32_t*)(GPIO_BASE+0x14)) = gpio11_cfg;
	/* output enable on gpio11 */
	*((uint32_t*)(GPIO_BASE+0x90)) = 1 << 11;
	/* output = 1 on gpio11 => on éteint la led */
	*((uint32_t*)(GPIO_BASE+0x88)) = 1 << 11;
}

/* ******************************************************* */
/* Stuff copied from bl_iot_sdk to understand what's wrong */
#define __NOP()				__asm volatile( "nop" );
#define BL_DRV_DUMMY                                 {__NOP();__NOP();__NOP();__NOP();}
#define GLB_SWRST_CFG1_OFFSET                                   (0x14)
#define GLB_SWRST_S10                                           GLB_SWRST_S10
#define GLB_SWRST_S10_POS                                       (0U)
#define GLB_SWRST_S10_LEN                                       (1U)
#define GLB_SWRST_S10_MSK                                       (((1U<<GLB_SWRST_S10_LEN)-1)<<GLB_SWRST_S10_POS)
#define GLB_SWRST_S10_UMSK                                      (~(((1U<<GLB_SWRST_S10_LEN)-1)<<GLB_SWRST_S10_POS))
#define GLB_SWRST_S11                                           GLB_SWRST_S11
#define GLB_SWRST_S11_POS                                       (1U)
#define GLB_SWRST_S11_LEN                                       (1U)
#define GLB_SWRST_S11_MSK                                       (((1U<<GLB_SWRST_S11_LEN)-1)<<GLB_SWRST_S11_POS)
#define GLB_SWRST_S11_UMSK                                      (~(((1U<<GLB_SWRST_S11_LEN)-1)<<GLB_SWRST_S11_POS))
#define GLB_SWRST_S12                                           GLB_SWRST_S12
#define GLB_SWRST_S12_POS                                       (2U)
#define GLB_SWRST_S12_LEN                                       (1U)
/* ******************************************************* */

void timer_init()
{
	/* enable toutes les clocks */
	*((volatile uint32_t*)(0x40000000)) |= 0b1111;
	/* enable clock pour timer */
	*((volatile uint32_t*)(0x40000024)) |= ((1 << 0x15) | 1) ;

	*((volatile uint32_t*)TCER_REG) &= (~0b111);

	/* timer interruption enable in the clic */
	*(volatile uint8_t*)(CLIC_HART0_ADDR + CLIC_INTIE + IRQ_CAUSE_TIMER1) = 1;
	*(volatile uint8_t*)(CLIC_HART0_ADDR + CLIC_INTIE + IRQ_CAUSE_TIMER2) = 1;

	/* clock 1kHz pour timer2 */
	*((volatile uint32_t*)TCCR_REG) &= (~(0b1101100));
	// *((volatile uint32_t*)TCCR_REG) |= 0bxx00000; //TIMER 2
	// *((volatile uint32_t*)TCCR_REG) |= 0b010xx00; //TIMER 1
	*((volatile uint32_t*)TCCR_REG) |= 0b1101100; //TIMER 1

	*((volatile uint32_t*)TCDR_REG) &= 0x000000FF;
	
	/* match with 1000 => T=1s a peu pres */
	*((volatile uint32_t*)TMR2_0_REG) = 1000;
	*((volatile uint32_t*)TMR2_1_REG) = 0xFFFFFFFE;
	*((volatile uint32_t*)TMR2_2_REG) = 0xFFFFFFFE;
	
	/* timer2 valeur par defaut 0 */
	*((volatile uint32_t*)TPLVR2_REG) = 0;
	
	/* timer2 preload a comparer avec match register 0 */
	*((volatile uint32_t*)TPLCR2_REG) &= (~(0b11));
	*((volatile uint32_t*)TPLCR2_REG) |= 1;
	
	/* preload pour timer2 => ca compte de 0 à match reg0 => interrupt puis compteur = match reg0*/
	*((volatile uint32_t*)TCMR_REG) &= (~(0b110));
	// *((volatile uint32_t*)TILR2_REG) &= (~(0b111));

	*((volatile uint32_t*)TICR2_REG) |= 0b111;
	
	/* enable interrupt on timer1 with match register 0 */
	*((volatile uint32_t*)TIER2_REG) &= (~0b111);
	*((volatile uint32_t*)TIER2_REG) |= 0b111;

	__asm volatile( "csrsi mstatus, 8" );
	/* count enable pour timer1 */
	*((volatile uint32_t*)TCER_REG) |= 0b010;


}

void bl602_main()
{
	gpio11_init();
	// timer_init();

	vPortSetupTimerInterrupt();
	bl_irq_init();
	
	*(volatile uint8_t*)configCLIC_TIMER_ENABLE_ADDRESS = 1;
	*(volatile uint8_t*)(CLINT_BASE_ADDR + CLIC_INTIE + 7) = 1;

	__asm volatile( "csrsi mstatus, 8" );
	
	while(1);
}
