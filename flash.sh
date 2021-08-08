#!/bin/bash
sudo ./blflash flash -w firmware.bin --port /dev/ttyUSB0 --initial-baud-rate 115200 --baud-rate 115200
