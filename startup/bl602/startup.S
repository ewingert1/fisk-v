
.section .init
.globl main
main:
    	# initialiser le handler d'exception
	#la t1, irq_handler
	#csrrw t1,mtvec,t1
	# t1 = 0
	#and t1,t1,x0
	# t1 = masque pour activer les interruptions (miep et mie flags) dans mstatus
	#ori t1,t1,0b10001000
	# commit dans mstatus
	#csrrs t2,mstatus,t1
	# t1 = 0
	#and t1,t1,x0
	# masque pour activer les Machine External Interrupt (b11) et Machine Timer Interrupt (b7)
	#li t1, 0b100010000000
	# enable les interrupts (stocke mie dans t2 puis OR mie avec t1)
	#csrrs t2,mie,t1
	
 	# initialiser le stack pointer a la fin de la ram : 0x42020000 + 64k = 0x42030000
	li sp, 0x42030000 
	# adresse configuration GPIO11 et GPIO10
	#li t1, 0x40000100
	# On met gpio11 en output (c'est le most significant 16bits, gpio_fun=11, le reste a 0)
	#li t2, 0b00001011010000000000000000000000
	#sw t2, 0x14(t1)
	# output enable	
	#li t2, 0b00000000000000000000100000000000
	#sw t2, 0x90(t1)
	# output = 1

	#not t3,t2
	#sw t3, 0x88(t1)

	jal bl602_main	

loop:
	wfi
	j loop

