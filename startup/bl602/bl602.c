
void bl602_irq_handler()
{

}

void bl602_main()
{
	unsigned int gpio_base = 0x40000100;
	unsigned int gpio11_cfg = 0b00001011001000000000000000000000;
	unsigned int gpio11_bit = 0b00000000000000000000100000000000;

	*((unsigned int*)(gpio_base+0x14)) = gpio11_cfg;
	*((unsigned int*)(gpio_base+0x90)) = gpio11_bit;
	// *((unsigned int*)(gpio_base+0x88)) = ~gpio11_bit;
}
