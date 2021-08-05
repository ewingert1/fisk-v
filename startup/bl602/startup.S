#define MSTATUS_FS      0x00006000

.section .init

.globl main
main:
	# Disable interrupts
	csrci mstatus, 8

	# initialiser le handler d'exception
	la t1, fiskv_handler
	# CLIC DIRECT MODE
	addi t1,t1,2
	csrw mtvec, t1

	# csrsi mstatus, 8

 	# initialiser le stack pointer a la fin de la ram : 0x42020000 + 64k = 0x42030000
	li sp, 0x42030000 
	jal bl602_main	

loop:
	wfi
	j loop


.globl allume
allume:
	li t4, 0x40000100
	sw x0, 0x88(t4) # 


.align 8
.globl fiskv_handler
fiskv_handler:
	li t4, 0x40000100
	sw x0, 0x88(t4) # 
	j allume
	mret
