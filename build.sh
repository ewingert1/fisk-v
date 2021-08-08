#!/bin/bash

riscv64-elf-gcc -L /usr/riscv32-elf/lib -I /usr/riscv32-elf/include/ -I drivers/ -DTARGET_BL602 -march=rv32imafc -mabi=ilp32 -mcmodel=medlow -nostartfiles -T linker/bl602/memmap.ld drivers/bl602/gpio.c drivers/bl602/timer.c drivers/bl602/irq.c startup/bl602/bl602.c startup/bl602/bl602.S -o firmware.elf
riscv32-elf-objcopy -O binary firmware.elf firmware.bin

