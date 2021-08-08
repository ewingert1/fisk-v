# FISK-V

Definitely not your new high-end RISC-V RTOS.

Mainly meant to learn about RISC-V Assembly and to tinker with low level programming on the new Pine64 BLE/Wifi powered BL602 SoC.
The goal is to have a minimal kernel able to run a few tasks.

Integrated timer works :p

TBD :

- done : jump to kr\_main
- done : switch led on
- done : enable timer/local interrupts on the CLIC 
- write a minimal Timer driver
- write a minimal GPIO driver
- write a minimal UART driver
- write a minimal PWM driver (blinky blinky)
- blink a led with gpio/pwmi
- print logs to fancy linux computer
- add a task queue
- implement context switching
- write a minimal scheduler
- call scheduler on timer tick
