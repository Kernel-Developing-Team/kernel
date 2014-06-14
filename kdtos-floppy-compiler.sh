#!/bin/bash
# Finally I have created a for the floppy drive!

sudo /sbin/losetup /dev/loop0 floppy/kdtos.img
sudo mount /dev/loop0 /mnt
sudo cp build/kernel.bin /mnt/kernel.bin
sudo umount /dev/loop0
sudo /sbin/losetup -d /dev/loop0
