OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH("riscv")

MEMORY{
    	RAM : ORIGIN = 0x42020000 , LENGTH = 256K
    	FLASH : ORIGIN = 0x23000000 , LENGTH = 16M
}


SECTIONS{
    	.init : { *(.init) } > FLASH 
    	.text : { *(.text) } > FLASH 
}

