
.section .init
.globl main
main:
	# initialiser le handler d'exception
	la t1, handler
	# mtvec <= t1 
	csrrw x0, mtvec, t1

	# MIE = 1
	li t1, 0b1000
	# commit dans mstatus
	# mstatus <= t1 
	csrrw x0,mstatus,t1
	# masque pour activer les Machine External Interrupt (bit 11) et Machine Timer Interrupt (bit 7)
	# masque pour activer les Machine External Interrupt (bit 11)
	li t1, 0b100000000000
	# enable les interrupts 
	# mie <= t1 
	csrrw x0,mie,t1
	
 	# initialiser le stack pointer a la fin de la ram : 0x42020000 + 64k = 0x42030000
	li sp, 0x42030000 
	jal bl602_main	

loop:
	wfi
	j loop

.section .text
handler:
	jal bl602_irq_handler
	mret
