#ifndef __MEMORY__H
#define __MEMORY__H

#include <types.h>
#include <settings.h>
#include <multiboot.h>

/***************************************************
 * Basic memory operations: alloc, free            *
 ***************************************************/
extern void* kmalloc (uint32 size);
extern void* kmalloc_a (uint32 size);
extern void* kmalloc_p (uint32 size, uint32* phys);
extern void* kmalloc_ap (uint32 size, uint32* phys);
extern void* kmrealloc (void* original, uint32 newsz);
extern void kfree (void* addr);

extern void MemoryTempInitialize (uint32 kernel_end);
extern void MemoryInitialize (MultibootInfo* info);

extern uint32 MemoryGetTotal();
extern uint32 MemoryGetFree(); // Returns total free physical memory in kilobytes
extern uint32 MemoryGetUsed(); // Total used physical memory in kbytes
extern uint32 MemoryGetFrameSize(); // Same as above functions, but in frames
extern uint32 MemoryGetFramesTotal();
extern uint32 MemoryGetFramesUsed();
extern uint32 MemoryGetFramesFree();


#endif
