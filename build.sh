#!/bin/dash
riscv64-elf-gcc -L /usr/riscv32-elf/lib -march=rv32imafc -mabi=ilp32f -nostartfiles -T linker/bl602/memmap.ld startup/bl602/* -o azerty
