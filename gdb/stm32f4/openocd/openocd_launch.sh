#!bin/sh
cd /tmp
openocd -f interface/stlink.cfg -f target/stm32f0x.cfg
