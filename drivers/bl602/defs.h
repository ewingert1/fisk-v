#include <stdint.h>

#define __NOP()				__asm volatile( "nop" );
#define BL_DRV_DUMMY        {__NOP();__NOP();__NOP();__NOP();}

/* Set mie (machine interrupt enable) in mstatus CSR => bit3 */
#define BL602_ENABLE_IRQ()    __asm volatile( "csrsi mstatus, 0b1000" );
/* Clear mie in mstatus */
#define BL602_DISABLE_IRQ()   __asm volatile( "csrci mstatus, 0b1000" );

/* BASE ADDRESSES */
#define GLB_BASE 	    0x40000000
#define GPIO_BASE 	    0x40000100
#define TIMER_BASE 		0x4000a500



/* INTERRUPT */
#define INT_CAUSE_SWI			3
#define INT_CAUSE_MTIMER		7
#define INT_CAUSE_EXTERNAL      11
#define INT_CAUSE_LOCAL			16
#define INT_CAUSE_TIMER2		INT_CAUSE_LOCAL + 36
#define INT_CAUSE_TIMER3		INT_CAUSE_LOCAL + 37

/* Partie CLINT du CLIC */
#define CLIC_SHARED_BASE			0x02000000
#define CLIC_MSIP          		    CLIC_SHARED_BASE
#define CLIC_MTIMECMP          		CLIC_SHARED_BASE + 0x4000
#define CLIC_MTIME          		CLIC_SHARED_BASE + 0xBFF8
#define CLIC_MTIME_L          		CLIC_MTIME
#define CLIC_MTIME_H          		CLIC_MTIME + 0x04

/* Partie CLIC spécifique : gère les IRQ locales + la préemption */
#define CLIC_HART0_BASE			CLIC_SHARED_BASE + 0x800000
#define CLIC_HART0_INTIP		CLIC_HART0_BASE
#define CLIC_HART0_INTIE		CLIC_HART0_BASE + 0x400
#define CLIC_HART0_INTCFG		CLIC_HART0_BASE + 0x800
#define CLIC_HART0_CFG		    CLIC_HART0_BASE + 0xC00


/* GLB REGISTERS */
#define GLB_CLK_CFG0            GLB_BASE
#define GLB_CLK_CFG1            GLB_BASE + 0x4
#define GLB_CLK_CFG2            GLB_BASE + 0x8
#define GLB_CLK_CFG3            GLB_BASE + 0xC


/* GPIO REGISTERS */
#define GPIO_CFGCTL0            GPIO_BASE
#define GPIO_CFGCTL1            GPIO_BASE + 0x04
#define GPIO_CFGCTL2            GPIO_BASE + 0x08
#define GPIO_CFGCTL3            GPIO_BASE + 0x0C
#define GPIO_CFGCTL4            GPIO_BASE + 0x10
#define GPIO_CFGCTL5            GPIO_BASE + 0x14
#define GPIO_CFGCTL6            GPIO_BASE + 0x18
#define GPIO_CFGCTL7            GPIO_BASE + 0x1C
#define GPIO_CFGCTL8            GPIO_BASE + 0x20
#define GPIO_CFGCTL9            GPIO_BASE + 0x24
#define GPIO_CFGCTL10           GPIO_BASE + 0x28
#define GPIO_CFGCTL11           GPIO_BASE + 0x2C
#define GPIO_CFGCTL12           GPIO_BASE + 0x30
#define GPIO_CFGCTL13           GPIO_BASE + 0x34
#define GPIO_CFGCTL14           GPIO_BASE + 0x38
#define GPIO_CFGCTL30           GPIO_BASE + 0x80
#define GPIO_CFGCTL32           GPIO_BASE + 0x88
#define GPIO_CFGCTL34           GPIO_BASE + 0x90

#define GPIO_INPUT_LEVEL        GPIO_CFGCTL30
#define GPIO_OUTPUT_LEVEL       GPIO_CFGCTL32
#define GPIO_OUTPUT_ENABLE      GPIO_CFGCTL34

/* TIMER REGISTERS */
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


