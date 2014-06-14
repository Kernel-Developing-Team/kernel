#ifndef __STDIO__H
#define __STDIO__H

#include <types.h>

#define inb(port) inportb(port)
#define outb(port) outportb(port)

extern uint8 inportb (uint16 _port);

static inline void outportb (uint16 _port, uint8 _data) {
      asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

static inline void iowait() {
      asm volatile ("outb %al, $0x80");
}

static inline void MagicBreakpoint()
{
	asm volatile ("xchg %bx, %bx");
}

extern void SystemReboot();

extern Key ReadKey();
extern KeyEvent ReadKeyEvent();

#endif
