/*
 * memory-add.h
 *
 *  Created on: Aug 27, 2011
 *      Author: Tiberiu
 */

#ifndef MEMORY_ADD_H_
#define MEMORY_ADD_H_

#include <memory.h>
#include <stdlib.h>
#include <debugio.h>
#include <array.h>

/***************************************************
 * Paging                                          *
 ***************************************************/
typedef uint32 Page;

enum PageFlags
{
	PagePresent = 0x1,
	PageWriteable = 0x2,
	PageUser = 0x4,
	PageWriteThough = 0x8,
	PageNotCacheable = 0x10,
	PageAccessed = 0x20,
	PageDirty = 0x40,
	PagePAT = 0x80,
	PageCpuGlobal = 0x100,
	PageLvl4Global = 0x200,
	PageFrame = 0xFFFFF000
};

typedef struct {
	Page Pages[1024];
} PageTable;

typedef struct {
	PageTable* Tables[1024];
	uint32 TablesPhysical[1024];
	uint32 PhysicalAddr;
} PageDirectory;

extern PageDirectory* CurrentDirectory;
extern PageDirectory* KernelDirectory;

extern void 	PagingEnable			();
extern void 	PagingDisable			();
extern void 	PagingSwitchDirectory	(PageDirectory* dir);
extern void 	PagingFlushTlb 			();
extern void 	PagingInitialize		(uint32* kernelEnd);
extern void 	PagingMapPage 			(uint32 phys, uint32 virt, uint32 flags, PageDirectory* pd);
extern void 	PagingUnmapPage 		(uint32 virt, PageDirectory* pd);
extern uint32 	PagingGetPhysical 		(uint32 virt, PageDirectory* pd);

/***************************************************
 * Physical memory manager                         *
 ***************************************************/
extern uint32 TotalBlocks;
extern uint32 TotalMemory;
extern uint32 UsedBlocks;

extern void 	MemPhInitialize		(uint32 SystemMemoryKb);
extern void 	MemPhSetBlock 		(uint32 Block, uint8 value);
extern uint32 	MemPhGetBlock 		(uint32 Block);
extern uint32 	MemPhAllocateBlock	();
extern void 	MemPhFreeBlock		(uint32 addr);
extern void 	MemPhReserveBlocks 	(uint32 address, uint32 length);


/***************************************************
 * Memory heap                                     *
 ***************************************************/
typedef struct
{
	OrderedArray Index;
	uint32 StartAddress, EndAddress, MaxAddress;
	// bit 0: supervisor-only  bit 1: read-only
	uint8 Flags;
} MemHeap;

extern MemHeap* KernelHeap;

extern uint32 	MemHeapFindSmallestHole	(uint32 size, uint8 page_align, MemHeap* heap);
extern int32 	MemHeapCompare 			(uint32 a, uint32 b);
extern MemHeap*	MemHeapCreate			(uint32 start, uint32 end, uint32 max, uint8 flags);
extern uint32 	MemHeapExpand			(uint32 newsz, MemHeap* heap, PageDirectory* pd);
extern uint32 	MemHeapContract			(uint32 newsz, MemHeap* heap, PageDirectory* pd);
extern uint32 	MemHeapAlloc 			(uint32 size, uint8 isPageAligned, MemHeap* heap, PageDirectory* pd);
extern void		MemHeapFree 			(uint32 address, MemHeap* heap, PageDirectory* pd);

#endif /* MEMORY_ADD_H_ */
