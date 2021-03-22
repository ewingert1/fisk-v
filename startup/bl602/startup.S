
.section .hdlrs
irq_handler:
	jal bl602_irq_handler	

.section .init
start:
    	# initialiser le handler d'exception
	la t1, irq_handler
	csrrw t1,mtvec,t1
	# t1 = 0
	and t1,t1,x0
	# t1 = masque pour activer les interruptions (miep et mie flags) dans mstatus
	ori t1,t1,0b10001000
	# commit dans mstatus
	csrrw t2,mtvec,t1
	# enable les interrupts
	csrrw t2,mtvec,t1
	
 	# initialiser le stack pointer a la fin de la ram : 0x42020000 + 64k = 0x42030000
	la sp , 0x42030000 
	#   
