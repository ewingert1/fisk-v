
.section .init
.globl main
main:
	# initialiser le handler d'exception
	li t1, handler
	csrrw t1,mtvec,t1
	# t1 = 0
	and t1,t1,x0
	# t1 = masque pour activer les interruptions (miep et mie flags) dans mstatus
	ori t1,t1,0b10001000
	# commit dans mstatus
	csrrs t2,mstatus,t1
	# t1 = 0
	and t1,t1,x0
	# masque pour activer les Machine External Interrupt (b11) et Machine Timer Interrupt (b7)
	li t1, 0b100010000000
	# enable les interrupts (stocke mie dans t2 puis OR mie avec t1)
	csrrs t2,mie,t1
	
 	# initialiser le stack pointer a la fin de la ram : 0x42020000 + 64k = 0x42030000
	li sp, 0x42030000 
	jal bl602_main	

loop:
	wfi
	j loop

.section .text
handler:
	jal irq_handler