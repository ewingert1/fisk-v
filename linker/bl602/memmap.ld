MEMORY{
    	RAM : ORIGIN = 0x42020000 , LENGTH = 256K
    	FLASH : ORIGIN = 0x23000000 , LENGTH = 16M
}


SECTIONS{
    	.init : { *(.init) } > FLASH 
    	.text : { *(.text) } > FLASH 
    	. = ADDR(.text) + SIZEOF(.text);
    	.hdlrs : { *(.hdlrs) } > FLASH
	.bss : { *(.bss)  } > RAM
    	.data : { *(.data)  } > RAM
}

