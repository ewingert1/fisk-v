#!/bin/bash

TOOLCHAIN_PREFIX="/home/wem/bl602_sdk/bl_iot_sdk/toolchain/riscv/Linux/bin/riscv64-unknown-elf"

riscv64-elf-gcc -L /usr/riscv32-elf/lib -march=rv32i -mabi=ilp32 -nostartfiles -T linker/bl602/memmap.ld startup/bl602/* -o firmware.elf
#riscv64-elf-as -march=rv32i -mabi=ilp32 startup/bl602/startup.S -o firmware.elf
riscv32-elf-objcopy -O binary firmware.elf firmware.bin

#riscv64-elf-as -march=rv32i -mabi=ilp32 test.S -o firmware.elf
#riscv32-elf-objcopy -O binary firmware.elf firmware.bin

#$TOOLCHAIN_PREFIX-as -o firmware.o startup/bl602/startup.S -march=rv32i -mabi=ilp32
#$TOOLCHAIN_PREFIX-ld -o firmware.elf firmware.o -m elf32lriscv
#$TOOLCHAIN_PREFIX-objcopy firmware.elf -O binary firmware.bin

