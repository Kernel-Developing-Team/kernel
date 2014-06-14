#!/bin/bash

# Copyright (C) 2014
# Author: Ian Sapelino

# Thank you to third party softwares for building the OS.

# Variables
EXPORTED=build
cc=gcc

clear

echo "KDTOS kernel is now rebuilding!"
echo "Please wait..."
echo "=============================="

sleep 3

echo " "
echo " "


echo "Compiling the boot.asm..."
echo "========================="



nasm -f elf -o $EXPORTED/boot.o kernel/boot.asm

sleep 3

echo " "
echo " "

echo "Compiling the kernel..."
echo "====================="



$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/main.o kernel/main.c

$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/screen.o kernel/hardwares/screen.c

$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/gdt.o kernel/libs/gdt.c

$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/idt.o kernel/libs/idt.c

$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/isrs.o kernel/libs/isrs.c

$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/irq.o kernel/libs/irq.c

$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/timer.o kernel/hardwares/timer.c


$cc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./kernel/include -c -o build/keyboard.o kernel/hardwares/keyboard.c

sleep 3

echo " "
echo " "

echo "Linking the booter and the kernel... Please wait."
echo "================================================="

sleep 3


ld -T kernel/link.ld -o $EXPORTED/kernel.bin $EXPORTED/boot.o $EXPORTED/main.o $EXPORTED/screen.o $EXPORTED/gdt.o $EXPORTED/idt.o $EXPORTED/isrs.o $EXPORTED/irq.o $EXPORTED/timer.o $EXPORTED/keyboard.o 



echo " "
echo " "

echo "The Process has been complete.. You can now test it, if you"
echo "Succeded the build of your patch, you can send it to my"
echo "github."

echo " "
echo " "

echo "If you contribute your code, Thank you for supporting the XaOS, another unix operating system :)."
