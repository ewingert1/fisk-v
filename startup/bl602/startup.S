
.section .init
.globl main
main:
	# initialiser le handler d'exception
	la t1, handler
	csrrw x0, mtvec, t1

	# Enable interrupts
	li t1, 0b1000
	csrrw x0,mstatus,t1
	
 	# initialiser le stack pointer a la fin de la ram : 0x42020000 + 64k = 0x42030000
	li sp, 0x42030000 
	jal bl602_main	

loop:
	wfi
	j loop

.section .text
.align 4
handler:
	jal bl602_irq_handler
	mret
