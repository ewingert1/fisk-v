#include "bl602/defs.h"
#include "timer.h"
#include "irq.h"

/* ******************************************************* */
/* Stuff copied from bl_iot_sdk to understand what's wrong */
uint64_t ullNextTime = 0ULL;
const uint64_t *pullNextTime = &ullNextTime;
uint32_t uxTimerIncrementsForOneTick = ( uint32_t ) 500000; 
volatile uint64_t * const pullMachineTimerCompareRegister = ( volatile uint64_t * const ) ( CLIC_MTIMECMP );
/* ******************************************************* */

void set_mtimer_interrupt()
{
	uint32_t ulCurrentTimeHigh, ulCurrentTimeLow;
	volatile uint32_t * const pulTimeHigh = ( volatile uint32_t * const ) ( CLIC_MTIME_H );
	volatile uint32_t * const pulTimeLow = ( volatile uint32_t * const ) ( CLIC_MTIME_L );

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
	enable_irq(INT_CAUSE_MTIMER);
}

void timer_init()
{
	// /* enable toutes les clocks */
	// *((volatile uint32_t*)(0x40000000)) |= 0b1111;
	// BL_DRV_DUMMY;
	// /* enable clock pour timer */
	// *((volatile uint32_t*)(0x40000024)) |= (0x3FFFF) ;
	// BL_DRV_DUMMY;
	// for (int j=0; j<50000; j++);

	*((volatile uint32_t*)TCER_REG) &= (~0b111);

	/* master clock for everyone */
	*((volatile uint32_t*)TCCR_REG) &= (~(0b1101100));

	*((volatile uint32_t*)TCDR_REG) &= 0x000000FF;
	
	/* match with 24000000 => T=1s a peu pres */
	*((volatile uint32_t*)TMR2_0_REG) = 24000000;
	*((volatile uint32_t*)TMR2_1_REG) = 24000000;
	*((volatile uint32_t*)TMR2_2_REG) = 24000000;
	
	/* timer2 valeur par defaut 0 */
	*((volatile uint32_t*)TPLVR2_REG) = 0;
	
	/* timer2 preload a comparer avec match register 0 */
	*((volatile uint32_t*)TPLCR2_REG) &= (~(0b11));
	*((volatile uint32_t*)TPLCR2_REG) |= 1;
	
	/* preload pour timer2 => ca compte de 0 à match reg0 => interrupt puis compteur = match reg0*/
	*((volatile uint32_t*)TCMR_REG) &= (~(0b110));
	*((volatile uint32_t*)TILR2_REG) &= (~(0b111));

	*((volatile uint32_t*)TICR2_REG) |= 0b111;
	
	/* enable interrupt on timer2 with match register 0 */
	*((volatile uint32_t*)TIER2_REG) &= (~0b111);
	*((volatile uint32_t*)TIER2_REG) |= 0b001;

	/* timer interruption enable in the clic */
	*(volatile uint8_t*)(CLIC_HART0_INTIE + INT_CAUSE_TIMER2) = 1;
	// *(volatile uint8_t*)(CLIC_HART0_INTIE_ADDR + IRQ_CAUSE_TIMER3) = 1;

	/* count enable pour timer2 */
	*((volatile uint32_t*)TCER_REG) |= 0b010;


}



